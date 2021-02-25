#pragma once


typedef struct tagVector2
{
	int x, y;

	tagVector2() {};
	tagVector2(int _x, int _y) : x(_x), y(_y) {};

}Vector2;

typedef struct tagTransform
{
	Vector2 Position;
	Vector2 Scale;

}Transform;

typedef struct tagNode
{
	int Index;
	int Option;
	int Cost;

}NODE;

typedef struct tagTile
{
	Vector2 Position;
	Vector2 Scale;

	int Index;
	int Option;
	int Cost;

	char* strTile[3];
}TILE;