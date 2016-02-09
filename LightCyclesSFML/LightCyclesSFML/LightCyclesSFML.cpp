#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "Game.h"
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
void Render();
void Update(int dt, Event& event);
void ConsoleDebugCallBack(string message, int priority);

//-----------------------------------------------------------
const string		GAME_NAME = "Light Cycles Game";
RenderWindow *		_window;
Event 				_event;
TextureManager *	_texture_manager;
Player *			_player;
HANDLE				hConsole;

//-----------------------------------------------------------
int main()
{
	//General init...
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_texture_manager = new TextureManager(&ConsoleDebugCallBack);
	_window = new RenderWindow(VideoMode(1280, 720), GAME_NAME);

	//Player init...
	_player = new Player();
	_player->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_player->SetTexture(_texture_manager->_cycle_texture);
	_player->setScale(Vector2f(1, 1));

	//Start the game...
	while (_window->isOpen())
	{
		while (_window->pollEvent(_event))
		{
			if (_event.type == Event::Closed)
				_window->close();
		}
		Render();
	}
	return 0;
}

//-----------------------------------------------------------
void Render()
{
	Clock clock;
	_window->clear();
	_window->draw(*_player);
	_window->display();

	auto timeElapsed = clock.getElapsedTime();
	clock.restart();
	Update(timeElapsed.asMilliseconds(), _event);
}

//-----------------------------------------------------------
void Update(int dt, Event& event)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		_window->close();
	}

	//Temporary for the funs, not the actual movement of the player...
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		_player->setPosition(_player->getPosition().x + DOWN_X * dt, _player->getPosition().y + DOWN_Y * dt);
		_player->setRotation(DOWN);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		_player->setPosition(_player->getPosition().x + UP_X * dt, _player->getPosition().y + UP_Y * dt);
		_player->setRotation(UP);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		_player->setPosition(_player->getPosition().x + LEFT_X * dt, _player->getPosition().y + LEFT_Y * dt);
		_player->setRotation(LEFT);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		_player->setPosition(_player->getPosition().x + RIGHT_X * dt, _player->getPosition().y + RIGHT_Y * dt);
		_player->setRotation(RIGHT);
	}
}

//-----------------------------------------------------------
void ConsoleDebugCallBack(string message, int color)
{
	//char* commandChr = const_cast<char*>(command.c_str());
	switch (color)
	{
	case 0:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "Message --> " << message << endl;
		break;
	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Success --> " << message << endl;
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Info --> " << message << endl;
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Error --> " << message << endl;
		break;
	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
