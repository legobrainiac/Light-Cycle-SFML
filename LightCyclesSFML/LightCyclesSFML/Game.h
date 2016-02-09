#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Player.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class Game
{

	//-----------------------------------------------------------
public:
	Game(string name, VideoMode mode);
	~Game();

	//-----------------------------------------------------------
private:
	string				_name;
	RenderWindow *		_window;
	VideoMode			_mode;
	Event 				_event;
	TextureManager *	_texture_manager;
	Player *			_player;

	//-----------------------------------------------------------
	void Update(float dt, Event &event);
	void Render();
	void Init();
};

