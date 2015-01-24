#pragma once
class BaseState
{
private:

public:
	BaseState();
	virtual ~BaseState();

	virtual bool Update(float dt);
	virtual void Render();
	virtual void Input();
};

