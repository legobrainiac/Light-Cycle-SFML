#include "Tile.h"

//-----------------------------------------------------------
Tile::Tile(Vector2f pos)
{
	setPosition(pos);
}

//-----------------------------------------------------------
Tile::~Tile()
{
}

//-----------------------------------------------------------
void Tile::SetTexture(Texture& tex)
{
	_sprite.setTexture(tex);
}

//-----------------------------------------------------------
void Tile::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}
