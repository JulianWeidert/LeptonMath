
#include <iostream>

#include <LeptonMath/Vector.h>

int main(){

	lm::Vector4f v = { 1,2,3,4 };

	auto v1 = v + v;

	std::cout << v1 << std::endl;

	v1[5] = 69.0f;

	std::cout << v1 << std::endl;

	return 0;
}
