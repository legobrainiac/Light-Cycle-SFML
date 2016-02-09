#include "Game.h"

//-----------------------------------------------------------
Game::Game(string name, VideoMode mode)
{
	_name = name;
	_mode = mode;
	_texture_manager = new TextureManager();
	_player = new Player();
	_player->SetSpriteTex(_texture_manager->_cycle_texture);
	Init();
}

//-----------------------------------------------------------
void Game::Init()
{
	_window = new RenderWindow(_mode, _name);

	while (_window->isOpen())
	{
		while (_window->pollEvent(_event))
		{
			if (_event.type == Event::Closed)
				_window->close();
		}
		Render();
	}
}

//-----------------------------------------------------------
void Game::Update(float dt, Event& event)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		
	}
}

//-----------------------------------------------------------
void Game::Render()
{
	Clock clock;

	_window->clear();
	
	_window->display();

	auto timeElapsed = clock.getElapsedTime();
	clock.restart();
	Update(timeElapsed.asMilliseconds(), _event);
}

//-----------------------------------------------------------
Game::~Game()
{
	delete _texture_manager;
	delete _window;
}
