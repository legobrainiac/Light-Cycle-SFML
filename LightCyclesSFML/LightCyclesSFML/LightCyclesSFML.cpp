#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "utils.h"
#include "AssetManager.h"
#include "Player.h"

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
AssetManager *		_asset_manager;
Player *			_player;
Text				_vert_count_player;
HANDLE				hConsole;

//-----------------------------------------------------------
int main()
{
	//General init...
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_asset_manager = new AssetManager(&ConsoleDebugCallBack);
	_window = new RenderWindow(VideoMode(1280, 720), GAME_NAME);

	//Player init...
	_player = new Player();
	_player->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_player->SetTexture(_asset_manager->_cycle_texture);
	_player->setScale(Vector2f(1, 1));
	_player->setPosition(Vector2f(1280, 400));

	//_vert_count_player init...
	_vert_count_player.setFont(_asset_manager->_sansation);
	_vert_count_player.setPosition(Vector2f(20,20));
	_vert_count_player.setScale(Vector2f(1,1));

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
	_window->draw(_player->GetTrail());
	_window->draw(_vert_count_player);
	_window->display();

	auto timeElapsed = clock.getElapsedTime();
	clock.restart();
	Update(timeElapsed.asMilliseconds(), _event);
}

//-----------------------------------------------------------
void Update(int dt, Event& event)
{
	_player->Update(dt);
	_vert_count_player.setString("Player trail vert count = " + to_string(_player->GetTrail().getVertexCount()));
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		_window->close();
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		ConsoleDebugCallBack(to_string(_player->GetTrail().getVertexCount()), INFO);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		_player->SetDirection(DOWN);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		_player->SetDirection(UP);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		_player->SetDirection(LEFT);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		_player->SetDirection(RIGHT);
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
