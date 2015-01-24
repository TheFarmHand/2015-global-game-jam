#pragma once
#include <vector>
#include "Object.h"
class Tiles;
class ObjectManager
{
private:
	std::vector<Object *> objects[3];//layer  0 = background, layer 1 = obstacles, layer 2 = player/npc
public:
	void AddObject(Object * _object, unsigned int layer);//adds object
	void RemoveObject(Object * _object);//does not handle memory, will find object and remove it from the manager
	void ClearAndDeleteAll();//handles memory
	void UpdateAll(float dt);//will update all objects in the manager in order of layer
	void RenderAll();//will render all objects in the manager in order of layer
	void CheckWorldCollision(unsigned int _bucket, Tiles * _tiles); // Check the given bucket with the world

	ObjectManager();
	~ObjectManager();
};

