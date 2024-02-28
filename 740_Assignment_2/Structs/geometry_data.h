#pragma once
#include <vector>
#include <GL/freeglut.h>

#include "vector3.h"

class geometry_data
{
public:
	std::vector<vector3> vertices; // Vertices
	float color[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Color
	const float point_size = 3.0f; // Point size
	GLenum draw_type = GL_LINE_LOOP; // Draw type of the object
};
