#include "Object.h"


Object::Object()
{
	SetType(OBJ_OBJECT);
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{

}

void Object::Render(void)
{

}

void Object::HandleCollision(Object * _object)
{
	//if (_object->GetType() == sometype)
	{

	}
}