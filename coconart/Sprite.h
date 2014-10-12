#pragma once
#include "Prerequites.h"
#include "ResourceTemplate.h"
#include <map>
using namespace std;

namespace Coconart
{

	class Sprite : public Resource
	{
	private:
		friend class BaseResourceManager<Sprite>;
		Sprite(const string& name) : Resource(name) {}
		Sprite(const Sprite& res);
	public:
		bool Load(const string& filename)
		{
			return true;
		}
	};

}