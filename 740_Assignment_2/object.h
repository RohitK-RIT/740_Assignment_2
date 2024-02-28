#pragma once
#include <string>

#include "Structs/transform.h"
#include "Structs/geometry_data.h"

class object
{
public:
	std::string name;
	transform* transform = new class transform(this);
	geometry_data* geometry_data = new class geometry_data();

	explicit object(const std::string& name);
};
