#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class Player : public Drawable, public Transformable
{

	//-----------------------------------------------------------
protected:
	Sprite			_sprite;
	VertexArrayPlus *	_trail;
	Clock			_clock;
	ROTATIONS		_rotation;
	string			_name;
	Color			_vertex_color;
	float			_speed = 0.2f;

	void(*ConsoleMessageCallBack)(string, int);
	void draw(RenderTarget& target, RenderStates states) const override;

	//-----------------------------------------------------------
public:
	void SetTexture(Texture &tex);
	void SetDirection(ROTATIONS rot);
	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	void SetSingularVertex();
	VertexArrayPlus& GetTrail() const;
	virtual void Update(int dt);
	void ClearTrail() const;
	Player();
	~Player();
};

