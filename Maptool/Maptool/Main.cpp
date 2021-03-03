#include "Headers.h"
#include "DoubleBuffer.h"


const int TILE_SIZE_X = 8;
const int TILE_SIZE_Y = 3;

const int TILE_COUNT_X = 120 / TILE_SIZE_X;
const int TILE_COUNT_Y = 30 / TILE_SIZE_Y;


NODE* GetNode(int _index, int _iCost, NODE* _pNode);
bool Compare(NODE* _pDestNode, NODE* _pSourNode);

int main(void)
{
	system("mode con cols=120 lines=31 | title Aster");
	DoubleBuffer::GetInstance()->CreateBuffer(121, 31);

	ULONGLONG Time = GetTickCount64();

	vector<TILE*> pTileList(TILE_COUNT_X * TILE_COUNT_Y);

	NODE* pNodeList = NULL;

	TILE Player;
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
			Tile->Cost = 1;
			Tile->Option = 0;
			Tile->Color = 15;

			pTileList[Tile->Index] = Tile;
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

	//** 출발지점
	int iStartIndex = 0;

	//** 도착 지점 셋팅.
	int iEndIndex;
	cout << "도착 지점 입력 : "; cin >> iEndIndex;
	pTileList[iEndIndex]->Option = 10;


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


			/***************************************************************************************************
			* 타일 검사 시작.
			****************************************************************************************************/



			//** 최 상위 부모 노드
			pNodeList = new NODE;
			pNodeList->Cost = 0;
			pNodeList->Index = Player.Index;
			pNodeList->Parent = NULL;



			//** 검사를 마친 노드.
			list<NODE*> CloseList;

			//** 확인 해야할 노드.
			list<NODE*> OpenList;

			//** 최종 노드를 담은 타일.
			list<int> BestList;

			NODE* pNode = NULL;

			while (true)
			{
				//** 죄측 검사.
				int iIndex = Player.Index - 1;
				if (iIndex >= 0 && pTileList[iIndex]->Position.x >= 0 &&
					(pTileList[iIndex]->Position.x + TILE_SIZE_X) <= pTileList[Player.Index]->Position.x &&
					pTileList[iIndex]->Option != 1)
				{
					pNode = GetNode(iIndex, pTileList[iIndex]->Cost, pNodeList);
					OpenList.push_back(pNode);
				}

				//** 상단 검사.
				iIndex = Player.Index - TILE_COUNT_X;
				if (iIndex >= 0 && pTileList[iIndex]->Position.y >= 0 &&
					(pTileList[iIndex]->Position.y + TILE_SIZE_Y) <= pTileList[Player.Index]->Position.y &&
					pTileList[iIndex]->Option != 1)
				{
					pNode = GetNode(iIndex, pTileList[iIndex]->Cost, pNodeList);
					OpenList.push_back(pNode);
				}

				//** 우측 검사.
				iIndex = Player.Index + 1;
				if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.x <= 120 &&
					pTileList[iIndex]->Position.x >= pTileList[Player.Index]->Position.x + TILE_SIZE_X &&
					pTileList[iIndex]->Option != 1)
				{
					pNode = GetNode(iIndex, pTileList[iIndex]->Cost, pNodeList);
					OpenList.push_back(pNode);
				}

				//** 하단 검사.
				iIndex = Player.Index + TILE_COUNT_X;
				if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.y <= 30 &&
					pTileList[iIndex]->Position.y >= (pTileList[Player.Index]->Position.y + TILE_SIZE_Y) &&
					pTileList[iIndex]->Option != 1)
				{
					pNode = GetNode(iIndex, pTileList[iIndex]->Cost, pNodeList);
					OpenList.push_back(pNode);
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

			/*

			//** 죄측 검사.
			int iIndex = Player.Index - 1;
			if (iIndex >= 0 && pTileList[iIndex]->Position.x >= 0 &&
				(pTileList[iIndex]->Position.x + TILE_SIZE_X) <= pTileList[Player.Index]->Position.x &&
				pTileList[iIndex]->Option != 1)
			{

				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y - 1, pTileList[iIndex]->strTile[0], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y, pTileList[iIndex]->strTile[1], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y + 1, pTileList[iIndex]->strTile[2], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x + 2, pTileList[iIndex]->Position.y, pTileList[iIndex]->Index);
			}

			//** 상단 검사.
			iIndex = Player.Index - TILE_COUNT_X;
			if (iIndex >= 0 && pTileList[iIndex]->Position.y >= 0 &&
				(pTileList[iIndex]->Position.y + TILE_SIZE_Y) <= pTileList[Player.Index]->Position.y &&
				pTileList[iIndex]->Option != 1)
			{
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y - 1, pTileList[iIndex]->strTile[0], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y, pTileList[iIndex]->strTile[1], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y + 1, pTileList[iIndex]->strTile[2], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x + 2, pTileList[iIndex]->Position.y, pTileList[iIndex]->Index);
			}

			//** 우측 검사.
			iIndex = Player.Index + 1;
			if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.x <= 120 &&
				pTileList[iIndex]->Position.x >= pTileList[Player.Index]->Position.x + TILE_SIZE_X &&
				pTileList[iIndex]->Option != 1)
			{
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y - 1, pTileList[iIndex]->strTile[0], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y, pTileList[iIndex]->strTile[1], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y + 1, pTileList[iIndex]->strTile[2], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x + 2, pTileList[iIndex]->Position.y, pTileList[iIndex]->Index);
			}
			
			//** 하단 검사.
			iIndex = Player.Index + TILE_COUNT_X;
			if (iIndex < (TILE_COUNT_X * TILE_COUNT_Y) && pTileList[iIndex]->Position.y <= 30 &&
				pTileList[iIndex]->Position.y >= (pTileList[Player.Index]->Position.y + TILE_SIZE_Y) &&
				pTileList[iIndex]->Option != 1)
			{
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y - 1, pTileList[iIndex]->strTile[0], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y, pTileList[iIndex]->strTile[1], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x, pTileList[iIndex]->Position.y + 1, pTileList[iIndex]->strTile[2], 10);
				//DoubleBuffer::GetInstance()->WriteBuffer(pTileList[iIndex]->Position.x + 2, pTileList[iIndex]->Position.y, pTileList[iIndex]->Index);

			}
			*/
			
		}
	}

	return 0;
}


NODE* GetNode(int _index, int _iCost, NODE* _pNode)
{
	NODE* pNode = new NODE;

	pNode->Index = _index;
	pNode->Cost = _pNode->Cost + _iCost;

	pNode->Parent = _pNode;
	//_pNode->Parent = pNode;


	return pNode;
}



bool Compare(NODE* _pDestNode, NODE* _pSourNode)
{
	return _pDestNode->Cost < _pSourNode->Cost;
}