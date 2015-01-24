#pragma once
class BaseState
{
private:

public:
	BaseState();
	virtual ~BaseState();

	virtual int Update(float dt);
	virtual void Render();
	virtual void Input();
};

