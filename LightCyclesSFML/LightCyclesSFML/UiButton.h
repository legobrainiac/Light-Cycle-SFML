#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class UiButton : public Drawable, public Transformable
{
	//-----------------------------------------------------------
private:
	Sprite			_sprite;
	int	_id;
	void(*ConsoleMessageCallBack)(string, int);
	void(*KeyCallBack)(UiButton&);

	//-----------------------------------------------------------
public:
	Text			Text;
	void draw(RenderTarget& target, RenderStates states) const override;
	void SetTexture(Texture &tex);
	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	void SetKeyCallBack(void(*KeyCallBackFunction)(UiButton&));
	void SetSize(Rect<int> buttonSize);
	void SetColor(Color color);
	void SetId(int id);
	int GetId() const;
	virtual void Update(int dt, RenderWindow& window);
	UiButton(Rect<int> buttonSize, Color color);
	UiButton();
	~UiButton();
};

