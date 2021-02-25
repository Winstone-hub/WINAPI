#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>

using namespace std;


typedef struct tagNode
{
	int Value;

	tagNode* Front;
	tagNode* Back;

}NODE;


void CreateNode(NODE* _List, int _Value)
{

	if (_List->Back == NULL)
	{
		NODE* pNode = new NODE;
		pNode->Front = _List;
		_List->Back = pNode;
		pNode->Back = NULL;
		pNode->Value = _Value;
	}
	else
		CreateNode(_List->Back, _Value);
}

void Output(NODE* _List)
{
	cout << _List->Value << endl;

	if (_List->Back != NULL)
	{
		Output(_List->Back);
	}
}


int main(void)
{
	NODE* List = NULL;
	int iCost = 0;

	ULONGLONG Time = GetTickCount64();

	while (true)
	{
		if (Time + 50 < GetTickCount64())
		{
			system("cls");
			if (GetAsyncKeyState(VK_RETURN))
			{
				if (List == NULL)
				{
					List = new NODE;
					List->Back = NULL;
					List->Front = NULL;

					List->Value = iCost;
				}
				else
				{
					CreateNode(List, iCost);
				}
				iCost++;
				Time = GetTickCount64();
			}

			if (List)
				Output(List);
		}
	}

	return 0;
}
