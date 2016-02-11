#include "UiButton.h"
#include <iostream>

//-----------------------------------------------------------
UiButton::UiButton(Rect<int> buttonSize, Color color)
{
	_sprite.setColor(color);
	_sprite.setTextureRect(buttonSize);
}

//-----------------------------------------------------------
UiButton::UiButton()
{
	_sprite.setTextureRect(Rect<int>(getPosition().x, getPosition().y, 32, 32));
}

//-----------------------------------------------------------
UiButton::~UiButton()
{
}

//-----------------------------------------------------------
void UiButton::Update(int dt, RenderWindow& window)
{
	if (_sprite.getTextureRect().contains(Mouse::getPosition(window)))
	{
		KeyCallBack(*this);
	}
}

//-----------------------------------------------------------
void UiButton::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}

//-----------------------------------------------------------
void UiButton::SetTexture(Texture& tex)
{
	_sprite.setTexture(tex);
	ConsoleMessageCallBack("Changed texture for UiButton...", INFO);
}

//-----------------------------------------------------------
void UiButton::SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
}

//-----------------------------------------------------------
void UiButton::SetKeyCallBack(void(*KeyCallBackFunction)(UiButton&))
{
	KeyCallBack = KeyCallBackFunction;
}

//-----------------------------------------------------------
void UiButton::SetSize(Rect<int> buttonSize)
{
	_sprite.setTextureRect(buttonSize);
}

//-----------------------------------------------------------
void UiButton::SetColor(Color color)
{
	_sprite.setColor(color);
}







