#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <time.h>

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
static int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);

//-----------------------------------------------------------
enum CONSOLE_COLORS {
	MESSAGE = 0,
	SUCCESS = 1,
	INFO = 2,
	ERRO = 3,
};

//-----------------------------------------------------------
enum DIRECTIONS
{
	UP_X = 0,
	UP_Y = -1,
	DOWN_X = 0,
	DOWN_Y = 1,
	LEFT_X = -1,
	LEFT_Y = 0,
	RIGHT_X = 1,
	RIGHT_Y = 0
};

//-----------------------------------------------------------
enum ROTATIONS
{
	LEFT = 0,
	RIGHT = 180,
	UP = 90,
	DOWN = 270
};

//-----------------------------------------------------------
static ROTATIONS GetRandomRotation(unsigned int seed)
{
	srand(seed);
	switch (rand() % 5)
	{
	case 1:
		return LEFT;
	case 2:
		return RIGHT;
	case 3:
		return DOWN;
	case 4:
		return UP;
	default:
		return DOWN;
	}
}

//-----------------------------------------------------------
static ROTATIONS GetOppositeRotation(ROTATIONS rot)
{
	switch (rot)
	{
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	default:
		break;
	}
}

//-----------------------------------------------------------
static bool IsInsideRect(Rect<int> rect, Vector2f pos)
{
	return rect.contains(pos.x, pos.y);
}

//-----------------------------------------------------------
static bool VertexArrayIntersect(vector<Vertex> array1, vector<Vertex> array2)
{
	//Not sure if this is going to be efficient, lets hope so... 
	//Idea: check vertex intersection by pairs...
	//I got help here: http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect


	for (size_t i = 0; i < array1.size(); i++)
	{
		Vertex vertices1[2]
		{
			array1[i],
			array1[i + 1]
		};

		for (size_t k = 0; k < array2.size(); k++)
		{
			Vertex vertices2[2]
			{
				array2[i],
				array2[i + 1]
			};

			//Logic goes here
			float x, y;
			if (
				get_line_intersection
				(
					vertices1[0].position.x,
					vertices1[0].position.y,
					vertices1[1].position.x,
					vertices1[1].position.y,
					vertices2[0].position.x,
					vertices2[0].position.y,
					vertices2[1].position.x,
					vertices2[1].position.y,
					&x,
					&y
					) == 1)
			{
				cout << x << " " << y << endl;
				return true;
			}
		}
	}

	// If they dont intersect return false
	return false;

}

//-----------------------------------------------------------
//Function by: http://stackoverflow.com/users/78216/gavin and improvement by http://stackoverflow.com/users/2058298/imalc
//http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
//-----------------------------------------------------------
static int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
	float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
	s10_x = p1_x - p0_x;
	s10_y = p1_y - p0_y;
	s32_x = p3_x - p2_x;
	s32_y = p3_y - p2_y;

	denom = s10_x * s32_y - s32_x * s10_y;
	if (denom == 0)
		return 0; // Collinear
	bool denomPositive = denom > 0;

	s02_x = p0_x - p2_x;
	s02_y = p0_y - p2_y;
	s_numer = s10_x * s02_y - s10_y * s02_x;
	if ((s_numer < 0) == denomPositive)
		return 0; // No collision

	t_numer = s32_x * s02_y - s32_y * s02_x;
	if ((t_numer < 0) == denomPositive)
		return 0; // No collision

	if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
		return 0; // No collision
				  // Collision detected
	t = t_numer / denom;
	if (i_x != nullptr)
		*i_x = p0_x + (t * s10_x);
	if (i_y != nullptr)
		*i_y = p0_y + (t * s10_y);

	return 1;
}

//-----------------------------------------------------------
// Allows me to add a function to the VertexArray.hpp, had to change the hpp file slightly 
// Changed (at line 183) private: to protected: so i could access m_vertices, didnt want to make it public...
//-----------------------------------------------------------
class VertexArrayPlus : public VertexArray
{
public:
	VertexArrayPlus(PrimitiveType type, size_t vertexCount = 0) : VertexArray(type, vertexCount) {}

	vector<Vertex> GetVertexArray() const
	{
		return m_vertices;
	}
};

