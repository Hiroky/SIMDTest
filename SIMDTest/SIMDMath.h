#pragma once

#include <immintrin.h>

typedef __m128 SIMDVector;
#define FORCEINLINE __forceinline

namespace SIMD {

	#define SIMD_SHUFFLEMASK(A0,A1,B2,B3) ((A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6))

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

	FORCEINLINE SIMDVector MakeVector(float x, float y, float z, float w)
	{
		return _mm_setr_ps(x, y, z, w);
	}

	FORCEINLINE SIMDVector LoadVector(const float* ptr)
	{
		return _mm_loadu_ps(ptr);
	}

	FORCEINLINE SIMDVector LoadVectorAligned(const float* ptr)
	{
		return _mm_load_ps(ptr);
	}

	FORCEINLINE SIMDVector LoadVectorFloat3(const float* ptr, float w = 0)
	{
		return MakeVector(ptr[0], ptr[1], ptr[2], w);
	}

	FORCEINLINE void StoreVector(float* ptr, SIMDVector v)
	{
		return _mm_storeu_ps(ptr, v);
	}

	FORCEINLINE void StoreVectorFloat1(float* ptr, SIMDVector v)
	{
		return _mm_store_ss(ptr, v);
	}

	FORCEINLINE void StoreVectorAligned(float* ptr, SIMDVector v)
	{
		return _mm_store_ps(ptr, v);
	}

	FORCEINLINE SIMDVector VectorAdd(SIMDVector a, SIMDVector b)
	{
		return _mm_add_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorSub(SIMDVector a, SIMDVector b)
	{
		return _mm_sub_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorMultiply(SIMDVector a, SIMDVector b)
	{
		return _mm_mul_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorDivide(SIMDVector a, SIMDVector b)
	{
		return _mm_div_ps(a, b);
	}

	// NOTE: 近似計算なので精度が低いことに注意
	FORCEINLINE SIMDVector VectorRcp(SIMDVector a)
	{
		return _mm_rcp_ps(a);
	}

	FORCEINLINE SIMDVector VectorSqrt(SIMDVector a)
	{
		return _mm_sqrt_ps(a);
	}

	// NOTE: 近似計算なので精度が低いことに注意
	FORCEINLINE SIMDVector VectorRsqrt(SIMDVector a)
	{
		return _mm_rsqrt_ps(a);
	}

	FORCEINLINE SIMDVector VectorMax(SIMDVector a, SIMDVector b)
	{
		return _mm_max_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorMin(SIMDVector a, SIMDVector b)
	{
		return _mm_min_ps(a, b);
	}

	FORCEINLINE SIMDVector VectorDot(SIMDVector a, SIMDVector b)
	{
#if 1
		// need SSE3
		SIMDVector m = VectorMultiply(a, b);
		m = _mm_hadd_ps(m, m);
		m = _mm_hadd_ps(m, m);
		return m;
#else
		SIMDVector m0, m1;
		m0 = VectorMultiply(a, b);
		m1 = VectorSwizzle<2, 3, 0, 1>(m0);
		m0 = VectorAdd(m0, m1);
		m1 = VectorSwizzle<1, 2, 3, 0>(m0);
		return VectorAdd(m0, m1);
#endif
	}

	FORCEINLINE SIMDVector VectorMultiplyAdd(SIMDVector a, SIMDVector b, SIMDVector c)
	{
		return _mm_add_ps(_mm_mul_ps(a, b), c);
	}

}


/**
 * operator overrides
 */
FORCEINLINE SIMDVector operator +(SIMDVector a, SIMDVector b)
{
	return SIMD::VectorAdd(a, b);
}

FORCEINLINE SIMDVector operator *(SIMDVector a, SIMDVector b)
{
	return SIMD::VectorMultiply(a, b);
}