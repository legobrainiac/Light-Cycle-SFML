#include "Player.h"

//-----------------------------------------------------------
Player::Player()
{
	_trail = new VertexArray(Lines, 200);
	_clock.restart();
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

//-----------------------------------------------------------
void Player::SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
}

//-----------------------------------------------------------
void Player::Update(int dt)
{
	if (_rotation == LEFT)
	{
		setPosition(getPosition().x + LEFT_X * _speed * dt, getPosition().y + LEFT_Y * _speed * dt);
		setRotation(LEFT);
	}
	else if (_rotation == RIGHT)
	{
		setPosition(getPosition().x + RIGHT_X * _speed * dt, getPosition().y + RIGHT_Y * _speed * dt);
		setRotation(RIGHT);
	}
	else if (_rotation == UP)
	{
		setPosition(getPosition().x + UP_X * _speed * dt, getPosition().y + UP_Y * _speed * dt);
		setRotation(UP);
	}
	else if (_rotation == DOWN)
	{
		setPosition(getPosition().x + DOWN_X * _speed * dt, getPosition().y + DOWN_Y * _speed * dt);
		setRotation(DOWN);
	}

	/*
	if (_clock.getElapsedTime().asMilliseconds() % 100 == 0) { }
	*/

	Vertex _vertex;
	_vertex.position = getPosition();
	_vertex.color = Color::Green;
	_trail->append(_vertex);
	_clock.restart();
	
}

//-----------------------------------------------------------
VertexArray& Player::GetTrail() const
{
	return *_trail;
}

//-----------------------------------------------------------
void Player::SetDirection(ROTATIONS rot)
{
	_rotation = rot;
}




