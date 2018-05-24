#include "statistics.h"
#include <limits.h>
#include <cmath>

Statistics::Statistics( int64_t samplesToSkip ):
mMean(0.0),
mPower(0.0),
mMin( 1.0e308 ),
mMax( -1.0e308 ),
mNumSamples(0),
mNumCalls(0),
mSamplesToSkip(samplesToSkip),
mHasRange(false),
mRangeMin(0),
mRangeMax(0)
{

}

Statistics::Statistics(double rangeMin, double rangeMax, int64_t samplesToSkip ):
mMean(0.0),
mPower(0.0),
mMin(  1.0e308 ),
mMax( -1.0e308 ),
mNumSamples(0),
mNumCalls(0),
mSamplesToSkip(samplesToSkip),
mHasRange(true),
mRangeMin(rangeMin),
mRangeMax(rangeMax)
{

}


Statistics::~Statistics(void)
{

}

void Statistics::Reset()
{
   mMean          = 0.0;
   mMin           = MaxPossibleValue;
   mMax           = MinPossibleValue;
   mPower         = 0.0;
   mNumSamples    = 0;
   mNumCalls      = 0;
}

void Statistics::SetSamplesToSkip( int64_t samplesToSkip )
{
   mSamplesToSkip = samplesToSkip;
}

void Statistics::AddSample( double x )
{
   if( (++mNumCalls) < mSamplesToSkip )
      return;

   if( mHasRange && ( x < mRangeMin || x > mRangeMax ) )
      return;

    mNumSamples++;
    double scale = ( static_cast<double>(mNumSamples) - 1.0 ) / static_cast<double>(mNumSamples);

    mMean = mMean * scale +  x  / static_cast<double>(mNumSamples);
    mPower = mPower * scale +  std::pow( x , 2 )  / static_cast<double>(mNumSamples);

    mMin = ( x < mMin ? x : mMin );
    mMax = ( x > mMax ? x : mMax );

}

double Statistics::NumSamples() const
{
   return static_cast<double>( mNumSamples );
}

double Statistics::Mean() const
{
  return mMean;
}
double Statistics::Min() const
{
  return mMin;
}
double Statistics::Max() const
{
  return mMax;
}
double Statistics::Power() const
{
  return mPower;
}
double Statistics::RMS() const
{
    return std::sqrt( Power() );
}
double Statistics::Variance() const
{
  return Power() - std::pow( Mean(), 2 );
}
double Statistics::StdDev() const
{
  return std::sqrt( Variance() );
}
