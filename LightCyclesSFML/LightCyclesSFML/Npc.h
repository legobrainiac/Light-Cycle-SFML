#pragma once

#include <SFML/Graphics.hpp>
#include "utils.h"
#include "Player.h"

//-----------------------------------------------------------
using namespace sf;
using namespace std;

//-----------------------------------------------------------
class Npc : public Player
{
	//-----------------------------------------------------------
public:
	void Update(int dt) override;
	void Reset();
	Npc();
	~Npc();
};

