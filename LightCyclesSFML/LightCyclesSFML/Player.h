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
	Sprite				_sprite;
	VertexArray *		_trail;
	Clock				_clock;
	ROTATIONS			_rotation;
	string				_name;
	float				_speed = 0.5f;

	void(*ConsoleMessageCallBack)(string, int);
	void draw(RenderTarget& target, RenderStates states) const override;

	//-----------------------------------------------------------
public:
	void SetTexture(Texture &tex);
	void SetDirection(ROTATIONS rot);
	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	VertexArray& GetTrail() const;
	virtual void Update(int dt);
	void ClearTrail() const;
	Player();
	~Player();
};

