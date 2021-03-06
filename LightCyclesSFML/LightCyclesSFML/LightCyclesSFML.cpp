#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "AssetManager.h"
#include "Npc.h"
#include "vector"
#include "Tile.h"
#include "UiButton.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
void Render();
void Update(int dt, Event& event);
void ConsoleDebugCallBack(string message, int priority);
void KeyCallBack(UiButton& button);

//-----------------------------------------------------------
const string		GAME_NAME = "Light Cycles Game";
const int			NPC_COUNT = 1;
const int			TILE_COUNT_SIDE = 40;
RenderWindow *		_window;
View				_view;
Event 				_event;
AssetManager *		_asset_manager;
Player *			_player;
vector<Npc*>		_npcs;
vector<Tile*>		_tiles;
vector<UiButton*>	_uiButtons;
HANDLE				_hConsole;

//--------------------------------------------- Ui components
UiButton			_buttonExit;
UiButton			_buttonResetBots;
UiButton			_buttonResetPlayer;
UiButton			_buttonAddBots;
UiButton			_buttonClearBots;
Text				_vert_count_player;

//-----------------------------------------------------------
int main()
{
	//General init...
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_asset_manager = new AssetManager(&ConsoleDebugCallBack);
	_window = new RenderWindow(VideoMode(1280, 720), GAME_NAME);
	_window->setFramerateLimit(60);
	_view.reset(FloatRect(0, 0, 1280, 720));

	//Player init...
	_player = new Player();
	_player->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_player->SetTexture(_asset_manager->_cycle_texture);
	_player->setScale(Vector2f(1, 1));
	_player->setPosition(Vector2f(200, 200));

	//Button init...
	_uiButtons.push_back(&_buttonExit);
	_buttonExit.SetKeyCallBack(&KeyCallBack);
	_buttonExit.SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_buttonExit.SetTexture(_asset_manager->_button_texture);
	_buttonExit.setPosition(10, 100);
	_buttonExit.SetSize(Rect<int>(_buttonExit.getPosition().x, _buttonExit.getPosition().y, 150, 50));
	_buttonExit.Text.setFont(_asset_manager->_sansation);
	_buttonExit.Text.setString("EXIT");
	_buttonExit.Text.setScale(0.7,0.7);
	_buttonExit.SetId(0);

	_uiButtons.push_back(&_buttonResetBots);
	_buttonResetBots.SetKeyCallBack(&KeyCallBack);
	_buttonResetBots.SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_buttonResetBots.SetTexture(_asset_manager->_button_texture);
	_buttonResetBots.setPosition(10, 160);
	_buttonResetBots.SetSize(Rect<int>(_buttonResetBots.getPosition().x, _buttonResetBots.getPosition().y, 150, 50));
	_buttonResetBots.Text.setFont(_asset_manager->_sansation);
	_buttonResetBots.Text.setString("RESET BOTS");
	_buttonResetBots.Text.setScale(0.7, 0.7);
	_buttonResetBots.SetId(1);

	_uiButtons.push_back(&_buttonResetPlayer);
	_buttonResetPlayer.SetKeyCallBack(&KeyCallBack);
	_buttonResetPlayer.SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_buttonResetPlayer.SetTexture(_asset_manager->_button_texture);
	_buttonResetPlayer.setPosition(10, 220);
	_buttonResetPlayer.SetSize(Rect<int>(_buttonResetPlayer.getPosition().x, _buttonResetPlayer.getPosition().y, 150, 50));
	_buttonResetPlayer.Text.setFont(_asset_manager->_sansation);
	_buttonResetPlayer.Text.setString("RESET PLAYER");
	_buttonResetPlayer.Text.setScale(0.7, 0.7);
	_buttonResetPlayer.SetId(2);

	_uiButtons.push_back(&_buttonAddBots);
	_buttonAddBots.SetKeyCallBack(&KeyCallBack);
	_buttonAddBots.SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_buttonAddBots.SetTexture(_asset_manager->_button_texture);
	_buttonAddBots.setPosition(Vector2f(10, 280));
	_buttonAddBots.SetSize(Rect<int>(_buttonAddBots.getPosition().x, _buttonAddBots.getPosition().y, 150, 50));
	_buttonAddBots.Text.setFont(_asset_manager->_sansation);
	_buttonAddBots.Text.setString("ADD BOT");
	_buttonAddBots.Text.setScale(0.7, 0.7);
	_buttonAddBots.SetId(3);

	_uiButtons.push_back(&_buttonClearBots);
	_buttonClearBots.SetKeyCallBack(&KeyCallBack);
	_buttonClearBots.SetConsoleMsgCallBack(&ConsoleDebugCallBack);
	_buttonClearBots.SetTexture(_asset_manager->_button_texture);
	_buttonClearBots.setPosition(Vector2f(10, 340));
	_buttonClearBots.SetSize(Rect<int>(_buttonClearBots.getPosition().x, _buttonClearBots.getPosition().y, 150, 50));
	_buttonClearBots.Text.setFont(_asset_manager->_sansation);
	_buttonClearBots.Text.setString("CLEAR BOTS");
	_buttonClearBots.Text.setScale(0.7, 0.7);
	_buttonClearBots.SetId(4);

	//Map init TODO: Should be in its own class for the heck of it...
	ConsoleDebugCallBack("Map gen started...", INFO);
	for (size_t x = 0; x < TILE_COUNT_SIDE; x++)
	{
		for (size_t y = 0; y < TILE_COUNT_SIDE; y++)
		{
			auto tile = new Tile(Vector2f(x * 32, y * 32));
			tile->SetTexture(_asset_manager->_tile);
			_tiles.push_back(tile);
		}
	}
	ConsoleDebugCallBack("Map gen finished...", SUCCESS);

	//Npc init...
	ConsoleDebugCallBack("Adding npc's...", INFO);
	for (size_t i = 0; i < NPC_COUNT; i++)
	{
		_npcs.push_back(new Npc());
	}

	for each(auto npc in _npcs)
	{
		npc->SetConsoleMsgCallBack(&ConsoleDebugCallBack);
		npc->SetTexture(_asset_manager->_cycle_texture);
	}

	//_vert_count_player init...
	_vert_count_player.setFont(_asset_manager->_sansation);
	_vert_count_player.setPosition(Vector2f(20, 20));
	_vert_count_player.setScale(Vector2f(1, 1));

	ConsoleDebugCallBack("Game started...", SUCCESS);
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
	//Map draw calls...
	for each(auto tile in _tiles)
	{
		_window->draw(*tile);
	}

	//Player and npc draw calls...
	_window->draw(*_player);

	for each(auto npc in _npcs)
	{
		_window->draw(*npc);
	}

	//Ui draw call...
	for each(auto button in _uiButtons)
	{
		_window->draw(*button);
	}

	//Debug draw calls...
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

	//Player movement...
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		_player->SetDirection(DOWN);
		_player->SetSingularVertex();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		_player->SetSingularVertex();
		_player->SetDirection(UP);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		_player->SetSingularVertex();
		_player->SetDirection(LEFT);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		_player->SetSingularVertex();
		_player->SetDirection(RIGHT);
	}

	//Collision detection	
	for each(auto npc in _npcs)
	{
		if (npc->GetTrail().GetVertexArray().size() > 1 && _player->GetTrail().GetVertexArray().size() > 1)
		{
			if (VertexArrayIntersect(npc->GetTrail().GetVertexArray(), _player->GetTrail().GetVertexArray()))
			{
				npc->Reset();
				_player->setPosition(Vector2f(200, 200));
				_player->ClearTrail();
				ConsoleDebugCallBack("Collision...", INFO);
			}
		}
	}

	//Ui Button
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for each(auto button in _uiButtons)
		{
			button->Update(dt, *_window);
		}
	}
}

//-----------------------------------------------------------
void KeyCallBack(UiButton& button)
{
	switch (button.GetId())
	{
	case 0:
		_window->close();
		break;
	case 1:
		for each(auto npc in _npcs)
		{
			npc->Reset();
		}
		break;
	case 2:
		_player->setPosition(Vector2f(200, 200));
		_player->ClearTrail();
		break;
	case 3:
		_npcs.push_back(new Npc(_asset_manager->_cycle_texture));
		break;
	case 4:
		_npcs.clear();
		_npcs.push_back(new Npc(_asset_manager->_cycle_texture));
		break;
	default:
		break;
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

