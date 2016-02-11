#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "AssetManager.h"
#include "Npc.h"
#include "vector"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
void Render();
void Update(int dt, Event& event);
void ConsoleDebugCallBack(string message, int priority);

//-----------------------------------------------------------
const string			GAME_NAME = "Light Cycles Game";
const int				NPC_COUNT = 3;
RenderWindow *			_window;
Event 					_event;
AssetManager *			_asset_manager;
Player *				_player;
vector<Npc*>			_npcs;
Text					_vert_count_player;
HANDLE					_hConsole;

//-----------------------------------------------------------
int main()
{
	//General init...
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_asset_manager = new AssetManager(&ConsoleDebugCallBack);
	_window = new RenderWindow(VideoMode(1280, 720), GAME_NAME);

	//Player init...
	_player = new Player();
	_player->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_player->SetTexture(_asset_manager->_cycle_texture);
	_player->setScale(Vector2f(1, 1));

	//Npc init...
	for (size_t i = 0; i < NPC_COUNT; i++)
	{
		//Npc* npc = new Npc();
	
		_npcs.push_back(new Npc());
	}

	for each(auto npc in _npcs)
	{
		npc->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
		npc->SetTexture(_asset_manager->_cycle_texture);
	}

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
	for each(auto npc in _npcs)
	{
		_window->draw(*npc);
		_window->draw(npc->GetTrail());
	}
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

	for each(auto npc in _npcs)
	{
		npc->Update(dt);
	}
	
	_vert_count_player.setString("Player trail vert count = " + to_string(_player->GetTrail().getVertexCount()));

	//General windows commands...
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		_window->close();
	}

	if (Keyboard::isKeyPressed(Keyboard::C))
	{
		_player->ClearTrail();
	}

	//Player movement...
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
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "Message --> " << message << endl;
		break;
	case 1:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Success --> " << message << endl;
		break;
	case 2:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Info --> " << message << endl;
		break;
	case 3:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Error --> " << message << endl;
		break;
	default:
		SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
	SetConsoleTextAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
