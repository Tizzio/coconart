#pragma once
#include "Prerequites.h"
#include "Libraries\jsoncpp\json.h"

namespace Coconart
{

	bool JsonLoad(Json::Value& root, const string& filename);

}