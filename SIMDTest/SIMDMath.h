#pragma once

#include <xmmintrin.h>

typedef __m128 SIMDVector;
#define FORCEINLINE __forceinline

namespace SIMD {

	#define SIMD_SHUFFLEMASK(A0,A1,B2,B3) ((A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6))

	FORCEINLINE SIMDVector MakeVector(float x, float y, float z, float w)
	{
		return _mm_setr_ps(x, y, z, w);
	}

	FORCEINLINE SIMDVector LoadVector(const float* ptr)
	{
		return _mm_loadu_ps(ptr);
	}

	FORCEINLINE SIMDVector VectorMultiply(SIMDVector a, SIMDVector b)
	{
		return _mm_mul_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorAdd(SIMDVector a, SIMDVector b)
	{
		return _mm_add_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorSub(SIMDVector a, SIMDVector b)
	{
		return _mm_sub_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorMax(SIMDVector a, SIMDVector b)
	{
		return _mm_max_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorMin(SIMDVector a, SIMDVector b)
	{
		return _mm_min_ps(a, b);
	}

	template <int index>
	FORCEINLINE SIMDVector VectorReplicate(SIMDVector a)
	{
		return _mm_shuffle_ps(a, a, SIMD_SHUFFLEMASK(index, index, index, index));
	}

	template <int x, int y, int z, int w>
	FORCEINLINE SIMDVector VectorSwizzle(SIMDVector a)
	{
		return _mm_shuffle_ps(a, a, SIMD_SHUFFLEMASK(x, y, z, w));
	}

	template <int x, int y, int z, int w>
	FORCEINLINE SIMDVector VectorShuffle(SIMDVector a, SIMDVector b)
	{
		return _mm_shuffle_ps(a, b, SIMD_SHUFFLEMASK(x, y, z, w));
	}
}


/**
 * operator overrides
 */
SIMDVector operator +(SIMDVector a, SIMDVector b)
{
	return SIMD::VectorAdd(a, b);
}

SIMDVector operator *(SIMDVector a, SIMDVector b)
{
	return SIMD::VectorMultiply(a, b);
}