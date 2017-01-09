// SIMDTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <assert.h>
#include <memory>
#include "SIMDMath.h"


#define ALIGN(n) __declspec(align(n))


/**
 * Vector4
 */
class Vector4
{
public:
	union {
		struct {
			float m[4];
		};
		struct {
			float x, y, z, w;
		};
	};

public:
	FORCEINLINE Vector4() {}
	FORCEINLINE Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	FORCEINLINE SIMDVector ToSIMD() const { return SIMD::LoadVector(m); }
};

typedef ALIGN(16) Vector4 AVector4;



struct Test
{
	float a;
	SIMDVector v;

	~Test()
	{
		a = 0;
	}
};




int main()
{
	AVector4 a(1, 1, 1, 1);
	auto& ra = (SIMDVector&)a;
	//auto mulA = ra * ra;
	auto mulA = _mm_mul_ps(ra, ra);

	AVector4 b(1, 0, 1, 0);
	//auto rb = b.ToSIMD();
	auto rb = _mm_load_ps((float*)&b);
	auto mulB = _mm_mul_ps(rb, rb);
	//auto mulB = rb * rb;

	auto dp = SIMD::VectorDot(ra, rb);

#if 0
	Vector4 a(1, 0.2f, 0.5f, 0.7f), b(2, 3, 5, 4);
	auto ra = a.ToSIMD();
	auto rb = b.ToSIMD();

	AVector4 alignedVec(1, 1, 1, 1);

	auto rmax = SIMD::VectorMax(ra, (SIMDVector&)alignedVec);
	auto swizzle = SIMD::VectorSwizzle<1, 1, 2, 3>(ra);
	auto mul = (SIMDVector&)alignedVec * (SIMDVector&)alignedVec;
#endif

#if 0
	size_t size = sizeof(Test);
	size_t align = alignof(Test);
	for (uint32_t i = 0; i < 100; i++) {
		void* m = _aligned_malloc(sizeof(Test), align);
		Test* a = new(m) Test();
		assert(((size_t)a & 0xff) == 0);
	}
#endif

	SIMD::StoreVectorAligned((float*)&a, ra);
	SIMD::StoreVectorAligned((float*)&b, rb);
	printf("%f, %f\n", a.x, b.x);

    return 0;
}

