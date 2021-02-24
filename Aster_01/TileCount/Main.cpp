#include "Headers.h"
#include "DoubleBuffer.h"


const int TILE_SIZE_X = 8;
const int TILE_SIZE_Y = 3;

const int TILE_COUNT_X = 120 / TILE_SIZE_X;
const int TILE_COUNT_Y = 30 / TILE_SIZE_Y;


int main(void)
{
	system("mode con cols=120 lines=31 | title Aster");
	DoubleBuffer::GetInstance()->CreateBuffer(121, 32);

	ULONGLONG Time = GetTickCount64();
	vector<TILE*> TileList;



	TILE Player;
	{
		Player.Position = Vector2(120 / 2, 30 / 2);
		Player.Scale = Vector2(0, 0);

		Player.strTile[0] = (char*)"";
		Player.strTile[1] = (char*)"";
		Player.strTile[2] = (char*)"";
	}




	for (int i = 0; i < TILE_COUNT_Y; ++i)
		for (int j = 0; j < TILE_COUNT_X; ++j)
		{
			TILE* Tile = new TILE;

			Tile->Scale.x = TILE_SIZE_X;
			Tile->Scale.y = TILE_SIZE_Y;

			Tile->strTile[0] = (char*)"忙式式忖";
			Tile->strTile[1] = (char*)"弛﹛﹛弛";
			Tile->strTile[2] = (char*)"戌式式戎";

			Tile->Position.x = j * Tile->Scale.x;
			Tile->Position.y = (i * Tile->Scale.y) + (Tile->Scale.y / 2);

			Tile->Index = i * TILE_COUNT_X + j;

			TileList.push_back(Tile);

			Tile->Option = 0;
		}

	int n = 0;

	srand((DWORD)GetTickCount64());

	while (true)
	{
		int iIndex = rand() % (TILE_COUNT_X * TILE_COUNT_Y);

		if (iIndex < 0 || iIndex >(TILE_COUNT_X * TILE_COUNT_Y))
			continue;


		if (TileList[iIndex]->Option != 1)
		{
			TileList[iIndex]->Option = 1;
			++n;
		}
		else
			continue;

		if (n == 5)
			break;
	}

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


			for (size_t i = 0; i < TileList.size(); ++i)
			{
				if (Player.Index == TileList[i]->Index)
				{
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y - 1, TileList[i]->strTile[0], 12);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y, TileList[i]->strTile[1], 12);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y + 1, TileList[i]->strTile[2], 12);
				}
				else if (TileList[i]->Option != 0)
				{
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y - 1, TileList[i]->strTile[0], 13);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y, TileList[i]->strTile[1], 13);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y + 1, TileList[i]->strTile[2], 13);
				}
				else
				{
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y - 1, TileList[i]->strTile[0]);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y, TileList[i]->strTile[1]);
					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x, TileList[i]->Position.y + 1, TileList[i]->strTile[2]);

					DoubleBuffer::GetInstance()->WriteBuffer(TileList[i]->Position.x + 2, TileList[i]->Position.y, TileList[i]->Index);
				}
			}


			int iIndex = Player.Index - 1;

			if (Player.Index > 0 && TileList[iIndex]->Position.x >= 0 && 
				(TileList[iIndex]->Position.x + TILE_SIZE_X) <= TileList[Player.Index]->Position.x &&
				TileList[iIndex]->Option != 1)
			{
				DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y - 1, TileList[iIndex]->strTile[0], 10);
				DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y, TileList[iIndex]->strTile[1], 10);
				DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y + 1, TileList[iIndex]->strTile[2], 10);
				DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x + 2, TileList[iIndex]->Position.y, TileList[iIndex]->Index);
			}

			iIndex = Player.Index - TILE_COUNT_X;
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y - 1, TileList[iIndex]->strTile[0], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y, TileList[iIndex]->strTile[1], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y + 1, TileList[iIndex]->strTile[2], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x + 2, TileList[iIndex]->Position.y, TileList[iIndex]->Index);

			iIndex = Player.Index + 1;
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y - 1, TileList[iIndex]->strTile[0], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y, TileList[iIndex]->strTile[1], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y + 1, TileList[iIndex]->strTile[2], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x + 2, TileList[iIndex]->Position.y, TileList[iIndex]->Index);

			iIndex = Player.Index + TILE_COUNT_X;
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y - 1, TileList[iIndex]->strTile[0], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y, TileList[iIndex]->strTile[1], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x, TileList[iIndex]->Position.y + 1, TileList[iIndex]->strTile[2], 10);
			DoubleBuffer::GetInstance()->WriteBuffer(TileList[iIndex]->Position.x + 2, TileList[iIndex]->Position.y, TileList[iIndex]->Index);

			DoubleBuffer::GetInstance()->WriteBuffer(Player.Position.x, Player.Position.y, (char*)"褡", 12);
		}
	}

	return 0;
}