#include "Headers.h"
#include "DoubleBuffer.h"





const int TILE_COUNT_X = 120 / 6;
const int TILE_COUNT_Y = 30 / 3;




int main(void)
{
	DoubleBuffer::GetInstance()->CreateBuffer(121, 31);

	ULONGLONG Time = GetTickCount64();


	while (true)
	{
		if (Time < GetTickCount64())
		{
			Time = GetTickCount64();
			
			DoubleBuffer::GetInstance()->FlippingBuffer();
			DoubleBuffer::GetInstance()->ClearBuffer();


			vector<TILE> TileList;

			for (int i = 0; i < TILE_COUNT_Y; ++i)
				for (int j = 0; j < TILE_COUNT_X; ++j)
				{
					TILE Tile;

					Tile.Scale.x = 6;
					Tile.Scale.y = 3;

					Tile.strTile[0] = (char*)"¦£¦¡¦¤";
					Tile.strTile[1] = (char*)"¦¢¡¡¦¢";
					Tile.strTile[2] = (char*)"¦¦¦¡¦¥";

					Tile.Position.x = j * Tile.Scale.x;
					Tile.Position.y = (i * Tile.Scale.y) + (Tile.Scale.y / 2);

					Tile.Index = i * TILE_COUNT_X + j;

					TileList.push_back(Tile);
				}

			for (size_t i = 0; i < TileList.size(); ++i)
			{
				DoubleBuffer::GetInstance()->WriteBuffer( TileList[i].Position.x, TileList[i].Position.y - 1, TileList[i].strTile[0]);
				DoubleBuffer::GetInstance()->WriteBuffer( TileList[i].Position.x, TileList[i].Position.y , TileList[i].strTile[1]);
				DoubleBuffer::GetInstance()->WriteBuffer( TileList[i].Position.x, TileList[i].Position.y + 1, TileList[i].strTile[2]);
				
				
				DoubleBuffer::GetInstance()->WriteBuffer( TileList[i].Position.x + 2, TileList[i].Position.y, TileList[i].Index);
			}
		}
	}













	


	return 0;
}