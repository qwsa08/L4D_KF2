#include "StdAfx.h"
#include "cMatrix.h"

//리ㅏ젇리ㅓㅈ버ㅐ;와아아아아아앙~~~~~~~~~~~~~~~~~~~~~~~~와아아아아ㅏ아아ㅏㅏㅏㅏㅏㅏ~~~~~~~~~와아아아아와와오아ㅗ아와
//와와와오아ㅗ오아ㅣ뫌노아ㅗ아ㅘ와~~~와~~
//와~~~~~~~~~ㅗ아와ㅗ아ㅘ와ㅗ아ㅗ아ㅗ아ㅘ와와와와와와와와
//무라무라무람루미ㅏㄴ위;ㅂㅈ이;ㅂㅈ;ㅡ비;즈입ㅈㅌ;ㅓㅟㅈ바ㅜㅏㅇㅈㅂ지ㅏㅜ지비
//asdgawrgrwhgaoiwurhgaiwuhvawlnvaiuwbvoiawuhbgaiouwrbvoilaw
//awejhgaouwihgoaiuwhg
cMatrix::cMatrix(void)
{
}


cMatrix::~cMatrix(void)
{
}
cMatrix::cMatrix(int nDimension)
{
	nDi = nDimension;
	vMatrix2.resize(nDi);
	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			//vMatrix[i].vVertical.push_back((rand() % 6 - 3) * 0.0001f);
			vMatrix2[i].push_back(FRAND);
			//vMatrix2[i].push_back(RAND);
		}
	}
}

void cMatrix::Resize(int nDimension)
{
	if (nDi == nDimension) return;
	//std::vector <tagMatrix> vTemp;
	cMatrix vTemp(nDi);
	std::vector <std::vector<float>> vTemp2;
	if (nDi > nDimension)
	{
		for (int i = 0; i < nDi; i++)
		{
			for (int j = 0; j < nDi; j++)
			{
				//vTemp[i].vVertical[j] = vMatrix[i].vVertical[j];
				vTemp.vMatrix2[i][j] = vMatrix2[i][j];
			}
		}
		vMatrix2.clear();
		nDi = nDimension;
		vMatrix2.resize(nDi);
		for (int i = 0; i < nDi; i++)
		{
			for (int j = 0; j < nDi; j++)
			{
				//vMatrix[i].vVertical[j] = vTemp[i].vVertical[j];
				vMatrix2[i].push_back(vTemp.vMatrix2[i][j]);
			}
		}
	}
	else
	{

		vMatrix2.resize(nDimension);
		for (int i = 0; i < nDimension; i++)
		{
			if (i < nDi)
			{
				for (int j = 0; j < nDimension - nDi; j++)
				{
					//vMatrix[i].vVertical.push_back((rand() % 6 -3) * 0.0001f);
					vMatrix2[i].push_back(FRAND);
				}
			}
			else
			{
				for (int j = 0; j < nDimension; j++)
				{
					vMatrix2[i].push_back(FRAND);
				}
			}
		}
		nDi = nDimension;
		
	}
	vTemp2.clear();
}
bool cMatrix::operator==(cMatrix m1)
{
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			//if (fabs((vMatrix[i].vVertical[j] - vMatrix[i].vVertical[j])) >= EPSILON) return false;
			if (fabs((vMatrix2[i][j] - m1.vMatrix2[i][j])) >= EPSILON) return false;
		}
	}

	return true;
}
bool cMatrix::operator!=(cMatrix m2)
{
	if (*this == m2) return false;
	return true;
}
cMatrix cMatrix::operator+(cMatrix m1)
{
	cMatrix temp(nDi);
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			//temp.vMatrix[i].vVertical[j] = (vMatrix[i].vVertical[j] + m1.vMatrix[i].vVertical[j]);
			temp.vMatrix2[i][j] = vMatrix2[i][j] + m1.vMatrix2[i][j];
		}
	}
	return temp;
}
cMatrix cMatrix::operator-(cMatrix m1)
{
	cMatrix temp(nDi);
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			//temp.vMatrix[i].vVertical[j] = (vMatrix[i].vVertical[j] - m1.vMatrix[i].vVertical[j]);
			temp.vMatrix2[i][j] = (vMatrix2[i][j] - m1.vMatrix2[i][j]);
		}
	}
	return temp;
}


cMatrix cMatrix::operator*(cMatrix m1)
{
	cMatrix temp(nDi);
	float test;
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			temp.vMatrix2[i][j] = 0;
			for (int k = 0; k < nDi; k++)
			{
				temp.vMatrix2[i][j] += vMatrix2[i][k] * m1.vMatrix2[k][j];
				test = temp.vMatrix2[i][j];
			}

		}
	}

	return temp;
}
cMatrix cMatrix::operator*(int n)
{
	cMatrix temp(nDi);
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			//temp.vMatrix[i].vVertical[j] = (vMatrix[i].vVertical[j] * n);
			temp.vMatrix2[i][j] = vMatrix2[i][j] * n;
		}
	}
	return temp;
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix Identi(nDimension);

	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			if (i == j) Identi.vMatrix2[i][j] = 1;
			else Identi.vMatrix2[i][j] = 0;
		}
	}
	
	return Identi;
}
cMatrix cMatrix::Transpose()
{
	cMatrix temp(nDi);
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			temp.vMatrix2[i][j] = vMatrix2[j][i];
		}
	}
	return temp;

}
cMatrix cMatrix::Inverse(float& fDeterminent)
{ 
	if (fDeterminent == 2)
	{
		(*this).Resize(fDeterminent);
		
		cMatrix temp(2);
		
		temp.vMatrix2[0][0] = (*this).vMatrix2[1][1];
		temp.vMatrix2[0][1] = -(*this).vMatrix2[0][1];
		temp.vMatrix2[1][0] = -(*this).vMatrix2[1][0];
		temp.vMatrix2[1][1] = (*this).vMatrix2[0][0];

		float detA = 1 / ((*this).vMatrix2[0][0] * (*this).vMatrix2[1][1] - (*this).vMatrix2[0][1] * (*this).vMatrix2[1][0]);
		if (detA == 0) return NULL;

	    return 1 / ((*this).vMatrix2[0][0] * (*this).vMatrix2[1][1] - (*this).vMatrix2[0][1] * (*this).vMatrix2[1][0]) * temp; 

	}
}
cMatrix cMatrix::Random(int nDimension) // -3~3
{
	srand(time(NULL));
	cMatrix temp(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			temp.vMatrix2[i][j] = 6 * ((float)rand() / (float)RAND_MAX) + (-3);
		}
	}
	
	return temp;

}
void cMatrix::Print()
{
	std::cout << std::fixed;
	std::cout.precision(2);
	for (int i = 0; i < nDi; i++)
	{
		for (int j = 0; j < nDi; j++)
		{
			std::cout << vMatrix2[i][j] << " \t";
		}
		std::cout << std::endl;
	}
}