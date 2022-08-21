
#include <iostream>
#include <span>
#include <algorithm>

#include <LeptonMath/Vector.h>
#include <LeptonMath/Matrix.h>

#include <immintrin.h>

typedef lm::Vector4f vec4;
typedef lm::Vector3f vec3;
typedef lm::Vector2f vec2;

class A {
	int i;
};

int main(){


	vec4 v1 = { 2, 4, 1, 7 };
	vec3 v2 = { 1, 5, 2 };


	auto res = lm::Vector<int, 3>({ 0,0,3 });


	std::cout << res.getNormalized() << std::endl;

	return 0;
}
