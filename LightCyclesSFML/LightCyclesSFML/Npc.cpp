#include "Npc.h"

//-----------------------------------------------------------
Npc::Npc() : Player()
{
	_name = "Npc";
	_vertex_color = Color::Red;
}

//-----------------------------------------------------------
Npc::~Npc()
{
}

//-----------------------------------------------------------
void Npc::Update(int dt)
{
	if ((_clock.getElapsedTime().asMilliseconds() > (rand() % 100 - 300)))
	{
		_rotation = GetRandomRotation(time(nullptr));
	}

	if (!IsInsideRect(Rect<int>(0, 0, 1280, 720), getPosition()))
	{
		Reset();
	}

	Player::Update(dt);
}

//-----------------------------------------------------------
void Npc::Reset()
{
	setPosition(Vector2f(840, 560));
	ClearTrail();
}

