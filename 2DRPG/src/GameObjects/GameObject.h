#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Input();
	virtual void Update(float dt);
	virtual void Render();

private:

};