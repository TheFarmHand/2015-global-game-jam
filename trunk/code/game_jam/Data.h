#pragma once

struct leveldata
{
	float gravity = 0.0f;
	void(*input)() = nullptr;//this will control the players input
	void(*render)() = nullptr;//this will control how things are rendered
	void(*update)(float dt) = nullptr;//this will change how things are rendered
	void(*keyupdate)(float dt) = nullptr;//this will change what the key does in the level
	void(*springupdate)(float dt) = nullptr;//this will change how the spring reacts to collision with the player
	void(*spikeupdate)(float dt) = nullptr;//this will change how the spike reacts to collision with the player
};
class Data
{
private:
	Data();
	~Data();
	Data(const Data& _rhs) = delete;
	Data& operator=(const Data& _rhs) = delete;
public:
	Data* GetInstance();//this class is for data and structs we need throughout the program
	unsigned int leveliter = 0;
	leveldata levels[10];

};
