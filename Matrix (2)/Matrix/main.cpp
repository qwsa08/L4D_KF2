// Matrix.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "cMatrix.h"

int _tmain(int argc, _TCHAR* argv[])
{

	cMatrix t1(3);
	cMatrix t2(3);

	t1.Print();
	std::cout << std::endl;
	t2.Print();

	if (t1 == t2) std::cout << "true" << std::endl;
	else std::cout << "false" << std::endl;
	std::cout << std::endl;

	cMatrix::Random(3).Print();
	return 0;
}

