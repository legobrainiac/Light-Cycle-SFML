#include "Player.h"

//-----------------------------------------------------------
Player::Player()
{
}

//-----------------------------------------------------------
Player::~Player()
{
}

//-----------------------------------------------------------
void Player::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

//-----------------------------------------------------------
void Player::SetTexture(Texture &tex)
{
	_sprite.setTexture(tex);
	ConsoleMessageCallBack("Changed player texture...", INFO);
}

void Player::SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
}
