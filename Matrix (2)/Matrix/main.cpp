// Matrix.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

