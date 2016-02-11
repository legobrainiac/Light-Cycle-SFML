#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class Tile : public Transformable, public Drawable
{
	//-----------------------------------------------------------
private:
	Sprite			_sprite;

	//-----------------------------------------------------------
public:
	void draw(RenderTarget& target, RenderStates states) const override;
	void SetTexture(Texture &tex);
	Tile(Vector2f pos);
	~Tile();
};

