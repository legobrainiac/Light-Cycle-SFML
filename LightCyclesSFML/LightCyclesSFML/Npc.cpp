#include "Npc.h"

//-----------------------------------------------------------
Npc::Npc(Texture &tex) : Player()
{
	seed = time(nullptr);
	_name = "Npc";
	_vertex_color = Color::Red;
	_sprite.setTexture(tex);
}

//-----------------------------------------------------------
Npc::Npc()
{
	seed = time(nullptr);
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
	if ((_clock.getElapsedTime().asMilliseconds() > (rand() % 100 - 800)))
	{
		srand(seed);
		Player::SetSingularVertex();
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
	setPosition(Vector2f(640, 360));
	ClearTrail();
}

