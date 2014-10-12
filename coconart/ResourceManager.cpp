#include "ResourceManager.h"

using namespace Coconart;

BaseResourceManager<Sprite> sprite_manager;


Sprite* ResourceManager::LoadSprite(const string& filename)
{
	return sprite_manager.LoadResource(filename);
}