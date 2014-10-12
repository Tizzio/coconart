#pragma once
#include "Prerequites.h"
#include "ResourceTemplate.h"
#include "Sprite.h"

namespace Coconart
{

	class ResourceManager
	{
	private:
		ResourceManager() {}
		ResourceManager(const ResourceManager& res) {}

	public:
		static Sprite* LoadSprite(const string& filename);
	};

}