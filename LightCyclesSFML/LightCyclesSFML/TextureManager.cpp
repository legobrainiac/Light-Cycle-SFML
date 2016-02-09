#include "TextureManager.h"

//-----------------------------------------------------------
TextureManager::TextureManager(void(*ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
	ConsoleMessageCallBack("Started loading textures...", INFO);
	LoadTextures();
	ConsoleMessageCallBack("Finished loading textures...", SUCCESS);
}

//-----------------------------------------------------------
TextureManager::~TextureManager()
{
}

//-----------------------------------------------------------
void TextureManager::SetConsoleMsgCallBack(void(* ConsoleMsgCallBack)(string, int))
{
	ConsoleMessageCallBack = ConsoleMsgCallBack;
}

//-----------------------------------------------------------
void TextureManager::LoadTextures()
{
	if (!_cycle_texture.loadFromFile("Assets/cycle.png"))
	{
		ConsoleMessageCallBack("Error loading texture...", ERRO);
	}
}

