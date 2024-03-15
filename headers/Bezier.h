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
		void drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& curveVertices1, std::vector<GLdouble>& curveVertices2, std::vector<GLdouble>& curveVertices3, std::vector<GLdouble>& curveVertices4, std::vector<GLdouble>& colors, int i, std::vector<GLdouble> mCurveNormals1, std::vector<GLdouble> mCurveNormals2, std::vector<GLdouble> mCurveNormals3, std::vector<GLdouble> mCurveNormals4);
	};
}