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
private:
	VertexArray	_vertices;
	Sprite	_sprite;
	void(*ConsoleMessageCallBack)(string, int);
	void draw(RenderTarget& target, RenderStates states) const override;

	//-----------------------------------------------------------
public:
	void SetTexture(Texture &tex);
	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	Player();
	~Player();
};

