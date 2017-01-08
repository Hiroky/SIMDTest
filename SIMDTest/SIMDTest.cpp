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
	Vector4 a(1, 0.2f, 0.5f, 0.7f), b(2, 3, 5, 4);
	auto ra = a.ToSIMD();
	auto rb = b.ToSIMD();

	auto rmax = SIMD::VectorMax(ra, rb);
	auto swizzle = SIMD::VectorSwizzle<1, 1, 2, 3>(ra);

#if 0
	size_t size = sizeof(Test);
	size_t align = alignof(Test);
	for (uint32_t i = 0; i < 100; i++) {
		void* m = _aligned_malloc(sizeof(Test), align);
		Test* a = new(m) Test();
		assert(((size_t)a & 0xff) == 0);
	}
#endif

    return 0;
}

