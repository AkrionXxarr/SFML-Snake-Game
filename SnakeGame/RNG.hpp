#ifndef _RNG_HPP_
#define _RNG_HPP_

#include <time.h>

/* Period parameters */
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df
#define CMATH_UPPER_MASK 0x80000000
#define CMATH_LOWER_MASK 0x7fffffff

/* Tempering parameters */
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y) (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y) (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y) (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y) (y >> 18)

class CRandom
{
public:
	CRandom();
	
	unsigned int Random(unsigned int n);
	void SetRandomSeed(unsigned int n);
	unsigned int GetRandomSeed();
	void Randomize();

protected:
	unsigned int rseed;
	unsigned long mt[CMATH_N];
	int mti;
};

#endif