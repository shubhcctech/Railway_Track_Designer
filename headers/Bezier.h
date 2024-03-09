#pragma once
#include "Point3D.h"
#include <vector>

namespace Feature
{
	class Bezier
	{
	public:
		Bezier();
		~Bezier();

		void drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors, int i);
		Geometry::Point3D calculateBezierPoint(std::vector<Geometry::Point3D>& controlPoints, double t);


	};
}