#include <Windows.h>
#include <iostream>


using namespace std;


int main(void)
{
	ULONGLONG Time = GetTickCount64();


	int Count = 0;


	while (true)
	{
		if (Time + 150 < GetTickCount64())
		{
			Time = GetTickCount64();

			system("cls");

			cout << Count++ << endl;
		}
	}




	return 0;
}