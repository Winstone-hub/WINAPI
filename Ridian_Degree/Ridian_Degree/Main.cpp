#include <Windows.h>
#include <iostream>
#include <math.h>

using namespace std;

#define PI 3.141592


float Ridian_Degree(float _Ridian)
{
	return float(_Ridian*(180/ PI));
}

float Degree_Ridian(float _Degree)
{
	return float((_Degree/180) * PI);
}

int main(void)
{
	float fAngle = 0.f;
	 


	/*
	while (true)
	{
		system("cls");
		if (GetAsyncKeyState(VK_UP))
		{
			fAngle += 5.f;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			fAngle -= 5.f;
		}

		cout << Degree_Ridian(fAngle) << endl;
	}
	*/

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_UP))
		{
			fAngle += 1.f;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			fAngle -= 1.f;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			fAngle += 0.141592f;
		}

		cout << Ridian_Degree(fAngle) << endl;
	}



	return 0;
}