
#include <iostream>

#include <LeptonMath/Vector.h>

int main(){

	lm::Vector4f v = { 1,2,3,4 };

	auto v1 = -v;
	auto v2 = v * v1;

	std::cout << v2 * v1 << std::endl;


	return 0;
}
