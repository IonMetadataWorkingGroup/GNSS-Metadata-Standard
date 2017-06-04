#ifndef CLASS_statistics
#define CLASS_statistics

#include <stdint.h>

class statistics
{

private:
   double  mMean;
   double  mPower;
   double  mDenominator;
   int64_t mNumSamples;

public:
   statistics( int64_t samplesToSkip = 0 );
   virtual ~statistics(void);

   const double  Mean()       const;
   const double  Power()      const;
   const double  RMS()        const;
   const double  Variance()   const;
   const double  StdDev()     const;
   const int64_t NumSamples() const;

   void AddSample( double x, double w );
   void AddSample( double x );
   void RemoveSample( double x, double w );
   void RemoveSample( double x );
   void Reset();
};

#endif //CLASS_statistics