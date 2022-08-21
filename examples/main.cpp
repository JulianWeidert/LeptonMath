
#include <iostream>
#include <span>
#include <algorithm>

#include <LeptonMath/Vector.h>
#include <LeptonMath/Matrix.h>


typedef lm::Vector4f vec4;
typedef lm::Vector3f vec3;
typedef lm::Vector2f vec2;




int main(){


	vec4 v1 = { 2, 4, 1, 7 };
	vec3 v2 = { 1, 5, 2 };

	auto res = lm::cross(v1.getXYZ(), v2);


	std::cout << res << std::endl;

	return 0;
}
