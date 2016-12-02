#pragma once
#include <vector>

struct tagMatrix
{
	std::vector<float> vVertical;
};
class cMatrix
{
public:
//	std::vector<tagMatrix> vMatrix;
	std::vector<std::vector<float>> vMatrix2;
	int nDi;
public:
	cMatrix(void);
	cMatrix(int nDimension);
	~cMatrix(void);

	void Resize(int nDimension);
	bool operator==(cMatrix m1);
	bool operator!=(cMatrix m2);
	cMatrix operator+(cMatrix m1);
	cMatrix operator-(cMatrix m1);
	cMatrix operator*(cMatrix m1);
	
	cMatrix operator*(int n);
	friend cMatrix operator*(int n, cMatrix m1)
	{
		cMatrix temp(m1.nDi);
		for (int i = 0; i < m1.nDi; i++)
		{
			for (int j = 0; j < m1.nDi; j++)
			{
				temp.vMatrix2[i][j] = m1.vMatrix2[i][j] * n;
			}
		}
		return temp;
	}

	// ==, !=, +, -, *(스칼라, 행렬)
	static cMatrix Identity(int nDimension);
	cMatrix Transpose();
	cMatrix Inverse(float& fDeterminent);
	static cMatrix Random(int nDimension);
	void Print();


	// 1 2 3
	// 4 5 6
	// 7 8 9 소수 둘째 자리.
};

