#include "statistics.h"
#include <stdint.h>
#include <limits.h>
#include <cmath>

statistics::statistics( int64_t samplesToSkip ):
mMean(0.0),
mPower(0.0),
mDenominator(0.0),
mNumSamples(0)
{

};




statistics::~statistics(void)
{

};

void statistics::Reset()
{
   mMean          = 0.0;
   mPower         = 0.0;
   mDenominator    = 1;
};

void statistics::AddSample( double x )
{
   AddSample( x, 1.0 );
}

void statistics::AddSample( double x, double w )
{

    mNumSamples++;
    mDenominator += w;
    double scale = ( mDenominator - 1.0 ) / mDenominator;

    mMean = mMean * scale +  x  / mDenominator;
    mPower = mPower * scale +  std::pow( x , 2 )  / mDenominator;

};

void statistics::RemoveSample( double x )
{
   RemoveSample( x, 1.0 );
}

void statistics::RemoveSample( double x, double w )
{
 
    mNumSamples--;
    mDenominator -= w;

    if( mNumSamples == 0 )
       Reset();

    double scale = ( mDenominator + 1.0 ) / mDenominator;

    mMean  = mMean  * scale -  x  / mDenominator;
    mPower = mPower * scale -  std::pow( x , 2 )  / mDenominator;

};


const int64_t statistics::NumSamples() const
{
   return mNumSamples;
};

const double statistics::Mean() const
{
  return mMean;
};

const double statistics::Power() const
{
  return mPower;
};

const double statistics::RMS() const
{
    return std::sqrt( std::abs(Power()) );
};

const double statistics::Variance() const
{
  return Power() - std::pow( Mean(), 2 );
};

const double statistics::StdDev() const
{
  return std::sqrt( std::abs(Variance()) );
};
