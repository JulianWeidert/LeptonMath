
#include <iostream>
#include <span>
#include <algorithm>

#include <LeptonMath/Vector.h>
#include <LeptonMath/Matrix.h>

int main(){


	lm::Matrix<int, 3, 3> mat = { {1,2,3},{4,5,6},{7,8,9} };
	lm::Vectori<3> vec = { 1,2,3 };

	auto res = mat * vec;

	std::cout << res << std::endl;


	return 0;
}
