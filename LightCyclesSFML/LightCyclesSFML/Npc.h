#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include "Player.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class Npc : public Player
{
private:
	int seed;

	//-----------------------------------------------------------
public:
	void Update(int dt) override;
	void Reset();
	Npc(Texture &tex);
	Npc();
	~Npc();
};

