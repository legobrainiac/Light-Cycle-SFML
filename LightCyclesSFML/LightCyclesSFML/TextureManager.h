#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;
 
//-----------------------------------------------------------
class TextureManager
{

	//-----------------------------------------------------------
private:
	void(*ConsoleMessageCallBack)(string, int);

	//-----------------------------------------------------------
public:
	Texture _cycle_texture;

	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	void LoadTextures();
	TextureManager(void(*ConsoleMsgCallBack)(string, int));
	~TextureManager();
};

