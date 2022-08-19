
#include <iostream>
#include <span>
#include <algorithm>

#include <LeptonMath/Vector.h>
#include <LeptonMath/Matrix.h>



int main(){


	lm::Matrix3x3f mat = { {1,2,3},{4,5,6},{7,8,9} };
	lm::Vector3f vec = { 1,2,3 };

	mat.transpose();
	//auto res1 = res * vec;

	std::cout << mat << std::endl;


	return 0;
}
