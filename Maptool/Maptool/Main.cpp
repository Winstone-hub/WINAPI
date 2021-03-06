#include "Headers.h"
#include "DoubleBuffer.h"


const int TILE_SIZE_X = 8;
const int TILE_SIZE_Y = 3;

const int TILE_COUNT_X = 120 / TILE_SIZE_X;
const int TILE_COUNT_Y = 30 / TILE_SIZE_Y;



//** 검사를 마친 노드.
list<NODE*> CloseList;

//** 확인 해야할 노드.
list<NODE*> OpenList;

//** 최종 노드를 담은 타일.
list<int> BestList;



vector<TILE*> pTileList;

//** 출발지점
int iStartIndex = 0;

//** 도착 지점
int iEndIndex;

//** 플레이어 
TILE Player;


NODE* GetNode(int _index, NODE** _pNode);
bool Compare(NODE* _pDestNode, NODE* _pSourNode);
bool CheckList(const int& _iIndex);
void MakeNode();


int main(void)
{
	system("mode con cols=120 lines=31 | title Aster");
	DoubleBuffer::GetInstance()->CreateBuffer(121, 31);

	ULONGLONG Time = GetTickCount64();

	{
		Player.Position = Vector2(120 / 2, 30 / 2);
		Player.Scale = Vector2(0, 0);

		Player.strTile[0] = (char*)"";
		Player.strTile[1] = (char*)"";
		Player.strTile[2] = (char*)"";
	}


	for (int i = 0; i < TILE_COUNT_Y; ++i)
	{
		for (int j = 0; j < TILE_COUNT_X; ++j)
		{
			TILE* Tile = new TILE;

			Tile->Scale.x = TILE_SIZE_X;
			Tile->Scale.y = TILE_SIZE_Y;

			Tile->strTile[0] = (char*)"┌──┐";
			Tile->strTile[1] = (char*)"│　　│";
			Tile->strTile[2] = (char*)"└──┘";

			Tile->Position.x = j * Tile->Scale.x;
			Tile->Position.y = (i * Tile->Scale.y) + (Tile->Scale.y / 2);

			Tile->Index = i * TILE_COUNT_X + j;
			Tile->Cost = 0;
			Tile->Option = 0;
			Tile->Color = 15;

			pTileList.push_back(Tile);
		}
	}


	int n = 0;
	srand((DWORD)GetTickCount64());


	while (true)
	{
		int iIndex = rand() % (TILE_COUNT_X * TILE_COUNT_Y);

		if (iIndex < 0 || iIndex >(TILE_COUNT_X * TILE_COUNT_Y))
			continue;


		if (n != 5 || pTileList[iIndex]->Option != 1)
		{
			pTileList[iIndex]->Option = 1;
			pTileList[iIndex]->Color = 13;

			++n;
		}
		else
			continue;

		if (n == 5)
			break;
	}

	

	//** 도착 지점 셋팅.
	cout << "도착 지점 입력 : "; cin >> iEndIndex;
	pTileList[iEndIndex]->Option = 10;



	bool Move = false;

	while (true)
	{
		if (Time < GetTickCount64())
		{
			Time = GetTickCount64();
			
			DoubleBuffer::GetInstance()->FlippingBuffer();
			DoubleBuffer::GetInstance()->ClearBuffer();

			if (GetAsyncKeyState(VK_UP))
			{
				if(Player.Position.y > 0)
					Player.Position.y -= 1;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (Player.Position.y < 29)
					Player.Position.y += 1;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (Player.Position.x > 0)
					Player.Position.x -= 1;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (Player.Position.x < 118)
					Player.Position.x += 1;
			}

			int iX = Player.Position.x / TILE_SIZE_X;
			int iY = Player.Position.y / TILE_SIZE_Y;

			Player.Index = iY * TILE_COUNT_X + iX;

			//** 출발지점 셋팅.
			iStartIndex = Player.Index;


			
			if (GetAsyncKeyState(VK_RETURN) && !Move)
			{
				MakeNode();
				Move = true;
			}

			if (Move && !BestList.empty())
			{
				Player.Position.x = pTileList[BestList.front()]->Position.x + 4;
				Player.Position.y = pTileList[BestList.front()]->Position.y;

				BestList.pop_front();
				Move = false;
			}

			

			for (size_t i = 0; i < pTileList.size(); ++i)
			{
				if (Player.Index == pTileList[i]->Index)
				{
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y - 1, pTileList[i]->strTile[0], 12);
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y, pTileList[i]->strTile[1], 12);
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y + 1, pTileList[i]->strTile[2], 12);
				}
				else
				{
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y - 1, pTileList[i]->strTile[0], pTileList[i]->Color);
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y, pTileList[i]->strTile[1], pTileList[i]->Color);
					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x, pTileList[i]->Position.y + 1, pTileList[i]->strTile[2], pTileList[i]->Color);

					DoubleBuffer::GetInstance()->WriteBuffer(pTileList[i]->Position.x + 2, pTileList[i]->Position.y, pTileList[i]->Index, pTileList[i]->Color);
				}
			}

			DoubleBuffer::GetInstance()->WriteBuffer(Player.Position.x, Player.Position.y, (char*)"옷", 12);
		}
	}

	return 0;
}

NODE* GetNode(int _index, NODE** _pNode)
{
	NODE* pNode = new NODE;

	pNode->Parent = (*_pNode);
	pNode->Index = _index;



	//int iCurCost = pTileList[_index]->Cost + pTileList[(*_pNode)->Index]->Cost;
	//int iEndCost = pTileList[_index]->Cost + pTileList[iEndIndex]->Cost;

	float fCurCostX = float(pTileList[(*_pNode)->Index]->Position.x - pTileList[_index]->Position.x);
	float fCurCostY = float(pTileList[(*_pNode)->Index]->Position.y - pTileList[_index]->Position.y);

	float fCurCost = sqrt((fCurCostX * fCurCostX) + (fCurCostY * fCurCostY));



	float fEndCostX = float(pTileList[iEndIndex]->Position.x - pTileList[_index]->Position.x);
	float fEndCostY = float(pTileList[iEndIndex]->Position.y - pTileList[_index]->Position.y);

	float fEndCost = sqrt((fEndCostX * fEndCostX) + (fEndCostY * fEndCostY));

	pNode->Cost = fCurCost + fEndCost;

	return pNode;
}

bool Compare(NODE* _pDestNode, NODE* _pSourNode)
{
	return _pDestNode->Cost < _pSourNode->Cost;
}

bool CheckList(const int& _iIndex)
{
	for (list<NODE*>::iterator iter = OpenList.begin(); iter != OpenList.end(); ++iter)
	{
		if ((*iter)->Index == _iIndex)
			return false;
	}

	for (list<NODE*>::iterator iter = CloseList.begin(); iter != CloseList.end(); ++iter)
	{
		if ((*iter)->Index == _iIndex)
			return false;
	}

	return true;
}


void MakeNode()
{
	/***************************************************************************************************
	* 타일 검사 시작.
	****************************************************************************************************/

	//** 최 상위 부모 노드
	NODE* pNodeList = new NODE;
	pNodeList->Cost = 0;
	pNodeList->Index = Player.Index;
	pNodeList->Parent = NULL;

	int iIndex = 0;


	while (true)
	{
		//** 죄측 검사.
		iIndex = pNodeList->Index - 1;
		if (iIndex >= 0 && pTileList[iIndex]->Position.x >= 0 &&
			(pTileList[iIndex]->Position.x + TILE_SIZE_X) <= pTileList[Player.Index]->Position.x &&
			pTileList[iIndex]->Option != 1 &&
			CheckList(iIndex))
		{
			OpenList.push_back(
				GetNode(iIndex, &pNodeList));
		}

		//** 상단 검사.
		iIndex = pNodeList->Index - TILE_COUNT_X;
		if (iIndex >= 0 && pTileList[iIndex]->Position.y >= 0 &&
			(pTileList[iIndex]->Position.y + TILE_SIZE_Y) <= pTileList[Player.Index]->Position.y &&
			pTileList[iIndex]->Option != 1 &&
			CheckList(iIndex))
		{
			OpenList.push_back(
				GetNode(iIndex, &pNodeList));
		}

		//** 우측 검사.
		iIndex = pNodeList->Index + 1;
		if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.x <= 120 &&
			pTileList[iIndex]->Position.x >= pTileList[Player.Index]->Position.x + TILE_SIZE_X &&
			pTileList[iIndex]->Option != 1 &&
			CheckList(iIndex))
		{
			OpenList.push_back(
				GetNode(iIndex, &pNodeList));
		}

		//** 하단 검사.
		iIndex = pNodeList->Index + TILE_COUNT_X;
		if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.y <= 30 &&
			pTileList[iIndex]->Position.y >= (pTileList[Player.Index]->Position.y + TILE_SIZE_Y) &&
			pTileList[iIndex]->Option != 1 &&
			CheckList(iIndex))
		{
			OpenList.push_back(
				GetNode(iIndex, &pNodeList));
		}


		OpenList.sort(Compare);
		list<NODE*>::iterator iter = OpenList.begin();

		pNodeList = (*iter);

		CloseList.push_back((*iter));
		OpenList.erase(iter);

		if (pNodeList->Index == iEndIndex)
		{
			while (true)
			{
				BestList.push_back(pNodeList->Index);
				pNodeList = pNodeList->Parent;

				if (pNodeList->Index == iStartIndex)
					break;
			}

			BestList.reverse();
			break;
		}
	}
}