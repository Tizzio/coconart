#pragma once
#include <map>
#include "Coconart.h"
using namespace std;

class GameObject
{
public:
	virtual void Create() = 0;
	virtual void Loop() = 0;
	virtual void Destroy() = 0;
};

class GameObjectManager
{
	map<uint, GameObject*> game_objects;

	void Loop()
	{
		for (auto it = game_objects.begin(); it != game_objects.end(); it++)
		{
			it->second->Loop();
		}
	}
};