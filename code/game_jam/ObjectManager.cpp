#include "ObjectManager.h"
#include "Tiles.h"
#include "GameState.h"

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
			objects[i][j]->Update(dt);
		}
	}
}
void ObjectManager::RenderAll()
{
	for (int i = 2; i >=0; i++)
	{
		for (unsigned int j = 0; j < objects[i].size(); j++)
		{
			objects[i][j]->Render();
		}
	}
}

void ObjectManager::CheckCollision(unsigned int _layer1, unsigned int _layer2)
{
	for (unsigned int i = 0; i < objects[_layer1].size(); i++)
	{
		for (unsigned int j = 0; j < objects[_layer2].size(); i++)
		{
			//if the objects here collide call the is intersecting function
			if (objects[_layer1][i]->GetRect().IsIntersecting(objects[_layer2][j]->GetRect()))
			{
				objects[_layer1][i]->HandleCollision(objects[_layer2][j]);
				objects[_layer2][j]->HandleCollision(objects[_layer1][i]);
			}
		}
	}

}

/**************************************************************/
// CheckCollisions
//	- check collision between the given bucket and the world
void ObjectManager::CheckWorldCollision(unsigned int _bucket, Tiles * _tiles)
{
	// Make sure there is something in the bucket to check
	if (_bucket >= 3 || objects[_bucket].size() == 0)
		return;

	// The vector of the given bucket
	std::vector<Object *> vec = objects[_bucket];

	// Loop through the bucket
	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		// Call the check collision function and pass in each entity
		_tiles->CheckCollision(vec[i]);
	}
}