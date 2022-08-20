
#include <iostream>
#include <span>
#include <algorithm>

#include <LeptonMath/Vector.h>
#include <LeptonMath/Matrix.h>


int main(){


	const lm::Vector4f vec = { 1,2,3,4 };
	

	std::cout << vec.getXY() << std::endl;


	return 0;
}
