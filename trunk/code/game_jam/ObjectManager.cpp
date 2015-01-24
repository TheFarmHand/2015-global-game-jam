#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}
void ObjectManager::AddObject(Object * _object, unsigned int layer)
{
	objects[layer].push_back(_object);
}
void ObjectManager::RemoveObject(Object * _object)
{
	for (int i = 0; i < 3 ; i++)
	{
		for (unsigned int j = 0; j < objects[i].size(); j++)
		{
			if (objects[i][j] == _object)
			{
				objects[i].erase(objects[i].begin());
			}
		}
	}
}
void ObjectManager::ClearAndDeleteAll()
{
	for (int i = 0; i < 3; i++)
	{
		while (objects[i].size())
		{
			delete objects[i].front();
			objects[i].erase(objects[i].begin());
		}
	}
}
void ObjectManager::UpdateAll(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < objects[i].size(); j++)
		{
			//objects[i][j]->Update(dt);
		}
	}
}
void ObjectManager::RenderAll()
{
	for (int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < objects[i].size(); j++)
		{
			//objects[i][j]->Render(dt);
		}
	}
}