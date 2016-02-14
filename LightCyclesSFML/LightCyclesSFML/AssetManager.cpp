#include <string>
#include <assert.h>
#include "AssetManager.h"

//-----------------------------------------------------------
AssetManager::AssetManager(void (*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
	ConsoleMessageCallBack("Started loading textures...", INFO);
	LoadTextures();
	ConsoleMessageCallBack("Finished loading textures...", SUCCESS);
}

//-----------------------------------------------------------
AssetManager::~AssetManager()
{
	
}

//-----------------------------------------------------------
void AssetManager::SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
}

//-----------------------------------------------------------
void AssetManager::LoadTextures()
{
	if (!_cycle_texture.loadFromFile("Assets/cycle.png"))
	{
		ConsoleMessageCallBack("Error loading cycle texture...", ERRO);
	}
	if (!_sansation.loadFromFile("Assets/sansation.ttf"))
	{
		ConsoleMessageCallBack("Error loading font...", ERRO);
	}
	if (!_tile.loadFromFile("Assets/tile.png"))
	{
		ConsoleMessageCallBack("Error loading tile texture...", ERRO);
	}
	if (!_button_texture.loadFromFile("Assets/button.png"))
	{
		ConsoleMessageCallBack("Error loading button texture...", ERRO);
	}
}

