#pragma once
#include "Prerequites.h"
#include <map>
using namespace std;

namespace Coconart
{

	template <typename T> class BaseResourceManager
	{
	public:
		map<string, T*> resources;

		T* CreateResource(const string& name)
		{
			T* res = new T(name);
			resources[name] = res;
			return res;
		}

		T* LoadResource(const string& filename)
		{
			T* res = CreateResource(filename);
			res->Load(filename);
			return res;
		}

		void DestroyResource(T* res)
		{
			resources.erase(res->name);
			delete res;
		}

		void DestroyResource(const string& name)
		{
			delete resources[name];
			resources.erase(name);
		}

		T* FindResource(const string& name)
		{
			return resources[name];
		}
	};



	class Resource
	{
	public:
		string name;
	protected:
		Resource(const string& new_name)
		{
			name = new_name;
		}
		Resource(const Resource& res);
	public:
		bool Load(const string& filename);

	};

}