#pragma once
#include "Player.h"
#include <string.h>
struct leveldata
{
	float gravity = 1400.0f;
	void(*input)(Player * _player, Tiles * _tiles) = nullptr;//this will control the players input
	void(*render)(GameState * _p) = nullptr;//this will control how things are rendered
	void(*update)(float dt) = nullptr;//this will change how things are rendered
	void(*keyupdate)(float dt) = nullptr;//this will change what the key does in the level
	void(*springupdate)(float dt) = nullptr;//this will change how the spring reacts to collision with the player
	void(*spikeupdate)(float dt) = nullptr;//this will change how the spike reacts to collision with the player
	std::string hint = "This is a hint";
};
class Data
{
private:
	Data();
	~Data();
	Data(const Data& _rhs) = delete;
	Data& operator=(const Data& _rhs) = delete;
public:
	static Data* GetInstance();//this class is for data and structs we need throughout the program
	unsigned int leveliter = 7;
	leveldata levels[11];

};

