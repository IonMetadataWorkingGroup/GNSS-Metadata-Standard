#ifndef CLASS_Statistics
#define CLASS_Statistics

#include <stdint.h>

class Statistics
{

private:
   double  mMean;
   double  mPower;
   double  mMin;
   double  mMax;
   int64_t mNumSamples;
   int64_t mNumCalls;
   int64_t mSamplesToSkip;
   bool    mHasRange;
   double  mRangeMin;
   double  mRangeMax;

public:
   Statistics( int64_t samplesToSkip = 0 );
   Statistics(double rangeMin, double rangeMax, int64_t samplesToSkip = 0 );
   virtual ~Statistics(void);

   const double MaxPossibleValue =  1.0e308;
   const double MinPossibleValue = -1.0e308;

   double Mean()       const;
   double Min()        const;
   double Max()        const;
   double Power()      const;
   double RMS()        const;
   double Variance()   const;
   double StdDev()     const;
   double NumSamples() const;

   void SetSamplesToSkip( int64_t samplesToSkip );
   
   void AddSample( double x );
   void Reset();
};

#endif //CLASS_Statistics
