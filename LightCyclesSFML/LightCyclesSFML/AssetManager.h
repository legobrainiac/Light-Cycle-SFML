#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "utils.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;
 
//-----------------------------------------------------------
class AssetManager
{

	//-----------------------------------------------------------
private:
	void(*ConsoleMessageCallBack)(string, int);

	//-----------------------------------------------------------
public:
	Texture _cycle_texture;
	Font _sansation;

	void SetConsoleMsgCallBack(void(*ConsoleMsgCallBack)(string, int));
	void LoadTextures();
	AssetManager(void(*ConsoleMsgCallBack)(string, int));
	~AssetManager();
};

