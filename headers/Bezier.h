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

		void drawCurve1D(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors);
		void drawCurve2D(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors);
		Geometry::Point3D calculateBezierPoint(std::vector<Geometry::Point3D>& controlPoints, double t);


	};
}