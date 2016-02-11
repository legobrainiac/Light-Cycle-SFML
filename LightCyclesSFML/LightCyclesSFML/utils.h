#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <time.h>

//-----------------------------------------------------------
using namespace sf;

//-----------------------------------------------------------
enum CONSOLE_COLORS {
	MESSAGE =	0,
	SUCCESS =	1,
	INFO =		2,
	ERRO =		3,
};

//-----------------------------------------------------------
enum DIRECTIONS
{
	UP_X =		0,
	UP_Y =		-1,
	DOWN_X =	0,
	DOWN_Y =	1,
	LEFT_X =	-1,
	LEFT_Y =	0,
	RIGHT_X =	1,
	RIGHT_Y =	0
};

//-----------------------------------------------------------
enum ROTATIONS
{
	LEFT =		0,
	RIGHT =		180,
	UP =		90,
	DOWN =		270
};

//-----------------------------------------------------------
static ROTATIONS GetRandomRotation(unsigned int seed) 
{
	srand(seed);
	switch (rand() % 5)
	{
	case 1:
		return LEFT;
		break;
	case 2:
		return RIGHT;
		break;
	case 3:
		return DOWN;
		break;
	case 4:
		return UP;
		break;
	default:
		return DOWN;
		break;
	}
}

//-----------------------------------------------------------
static ROTATIONS GetOppositeRotation(ROTATIONS rot)
{
	switch (rot)
	{
	case LEFT:
		return RIGHT;
		break;
	case RIGHT:
		return LEFT;
		break;
	case UP:
		return DOWN;
		break;
	case DOWN:
		return UP;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------
static bool IsInsideRect(Rect<int> rect, Vector2f pos)
{
	return rect.contains(pos.x, pos.y);
}
