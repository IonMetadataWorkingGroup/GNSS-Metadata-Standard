/**
 * File: Date.cpp
 * Author: M.B. Mathews
 *  
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *  
 * This Metadata API is free software; you can redistribute it and/or
 * modify it under the terms of the Lesser GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GnssMetadata/Date.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#if defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
#else
	#define _snprintf snprintf
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

using namespace GnssMetadata;

//time_t value for GPS0 in Windows.
#define GPS0 315964800
#define SECONDS_IN_WEEK (86400*7)
#define BILLION_VALUE (1000000000)
/******************************************************************************
* timespec utilities
******************************************************************************/

static time_t UtcYmdhmsToTime_T(int year, int mon, int day, int hour, int min, int sec)
{   struct tm *temp_tm;
	time_t temp_time_t;
	time(&temp_time_t);
	temp_tm = gmtime(&temp_time_t);
	temp_tm->tm_sec = sec;
	temp_tm->tm_min = min;
	temp_tm->tm_hour = hour;
	temp_tm->tm_mday = day;
	temp_tm->tm_mon = mon;
	temp_tm->tm_year = (year > 1900 ? year - 1900 : year);
	temp_time_t=mktime(temp_tm);    
#if defined(_POSIX_C_SOURCE)
	temp_time_t -= timezone;    // undo any correction for timezone/daylight savings system did
#else
	temp_time_t -= _timezone;   // undo any correction for timezone/daylight savings system did
#endif

	return temp_time_t;
}

/******************************************************************************
* Date class implementation
******************************************************************************/

Date Date::Now()
{
	Date date;
#if defined(_POSIX_C_SOURCE)
    clock_gettime( CLOCK_REALTIME, &(date._dt));
#elif defined(_WIN32) || defined(_WIN64)
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	ULARGE_INTEGER ull;    
	ull.LowPart = ft.dwLowDateTime;    
	ull.HighPart = ft.dwHighDateTime;    
	ull.QuadPart -= 116444736000000000ULL; // Since Jan 1 1970.
	time_t t = (time_t) (ull.QuadPart / 10000000ULL);
	ull.QuadPart -= t*10000000ULL; //Fractional 100 nano seconds.
	date._dt.tv_sec  = t;
	date._dt.tv_nsec = (ull.LowPart)*100;
#elif defined(__MACH__) // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	date._dt.tv_sec = mts.tv_sec;
	date._dt.tv_nsec = mts.tv_nsec;
#endif
	return date;
}

Date::Date() : _secLeap(0)
{
	_dt.tv_nsec = 0;
	_dt.tv_sec = 0;
}

Date::Date( const Date& rhs)
: _dt(rhs._dt), _secLeap( rhs._secLeap)
{

}
Date::Date( const IonTimespec& tspec)
: _dt( tspec), _secLeap(0)
{
}
Date::Date(int year, int mon, int day, int hour, int min, double sec)
: _secLeap(0)
{
	_dt.tv_sec = UtcYmdhmsToTime_T(year,mon-1,day,hour,min,(int)sec);
    _dt.tv_nsec = (long)((sec - floor(sec))*BILLION_VALUE);
}
Date::Date(time_t time, double fracsec)
: _secLeap(0)
{
	_dt.tv_sec = time;
	_dt.tv_nsec = (long)(fracsec*1e9);
}
Date::Date( double secGps, int wkGps, int secLeap )
: _secLeap(secLeap)
{
	time_t tsecGps = (time_t) secGps;
	_dt.tv_sec = (time_t)(wkGps*SECONDS_IN_WEEK) + tsecGps + (time_t) _secLeap;
	_dt.tv_sec += GPS0;
    _dt.tv_nsec = (long)((secGps - (double)tsecGps)*BILLION_VALUE);
}

Date::Date( const char* pszDate)
{
	int yr,mo,day,hr,min;
	double sec;

	//2012-10-12T00:06:12.314532
    sscanf( pszDate,
		"%d-%d-%dT%d:%d:%lf",
		&yr, &mo, &day, &hr, &min, &sec);

	_dt.tv_sec = UtcYmdhmsToTime_T(yr,mo-1,day,hr,min,(int)sec);
    _dt.tv_nsec = (long)((sec - floor(sec))*BILLION_VALUE);

}

const Date& Date::operator=( const Date& rhs)
{
	if( &rhs != this)
	{
		_dt = rhs._dt;
		_secLeap = rhs._secLeap;
	}
	
	return *this;
}

/**
 * Returns a string representation of the object.
 */
IonString Date::toString( const IonString & /*sFormat*/ ) const
{
	char buff[64];
	struct tm utc;
	TmPtr(&utc);
    double dsec = (double)utc.tm_sec + (double)_dt.tv_nsec*1e-9;

	//2012-10-12T00:06:12.314532Z
	sprintf(buff, "%4d-%02d-%02dT%02d:%02d:%0.9lfZ",
		utc.tm_year+1900, utc.tm_mon+1, utc.tm_mday,
		utc.tm_hour, utc.tm_min, dsec);

	return IonString( buff);
}

IonTimespec Date::SinceGps0() const
{ 
	IonTimespec gt = _dt; 
	gt.tv_sec -= (GPS0 + _secLeap);
	return gt;
}

/**
 * Returns the GPS week and seconds 
 */
void Date::ToGpsWeekSec( int *pwkGps, double *psecGps) const
{
	IonTimespec gt = _dt; 
	gt.tv_sec -= (GPS0 + _secLeap);
	*pwkGps = (int) (gt.tv_sec / SECONDS_IN_WEEK);
	*psecGps = (double)(gt.tv_sec - (time_t)(SECONDS_IN_WEEK*(*pwkGps))); 
    *psecGps += ((double)gt.tv_nsec*1e-9);
}