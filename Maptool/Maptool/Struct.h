#pragma once


typedef struct tagVector2
{
	int x, y;

	tagVector2() : x(0), y(0) {};
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
	int Cost;

	tagNode* Parent;

}NODE;

typedef struct tagTile
{
	Vector2 Position;
	Vector2 Scale;

	int Index;
	int Option;
	int Cost;
	int Color;

	char* strTile[3];
}TILE;