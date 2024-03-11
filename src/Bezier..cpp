#include "stdafx.h"
#include "Bezier.h"
#include <cmath>

Feature::Bezier::Bezier()
{

}
Feature::Bezier::~Bezier()
{

}

<<<<<<< HEAD
		double term = binomialCoefficient * pow(1 - t, n - i) * pow(t, i);
		x += controlPoints[i].x() * term;
		y += controlPoints[i].y() * term;
		z += controlPoints[i].z() * term;
	}
	return Geometry::Point3D(x, y, z);
}

void Feature::Bezier::drawCurve1D(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors)
{
	OutputDebugStringA("drawCurve-1D called\n");
	for (double t = 0; t <= 1; t += 0.001)
	{
		Geometry::Point3D bezierPoint = calculateBezierPoint(controlPoints, t);
		vertices.push_back(bezierPoint.x());
		vertices.push_back(bezierPoint.y());
		vertices.push_back(bezierPoint.z());

		colors.push_back(0.0);
		colors.push_back(1.0);
		colors.push_back(0.0);

		/*vertices.push_back(bezierPoint.x());
		vertices.push_back(bezierPoint.y() + 4);
		vertices.push_back(bezierPoint.z());

		colors.push_back(0.0);
		colors.push_back(1.0);
		colors.push_back(0.0);*/
	}
}
void Feature::Bezier::drawCurve2D(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors)
{
	OutputDebugStringA("drawCurve-2D called\n");
	for (double t = 0; t <= 1; t += 0.001)
=======
void Feature::Bezier::drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors, int i)
{
	for (float u = 0; u <= 1; u += 0.001)
>>>>>>> c2919797ac1910363d74c081458f16265e052fa8
	{

		float x = pow(1 - u, 3) * controlPoints[0].x() + 3 * pow(1 - u, 2) * u * controlPoints[1].x() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].x() + pow(u, 3) * controlPoints[3].x();
		float y = pow(1 - u, 3) * controlPoints[0].y() + 3 * pow(1 - u, 2) * u * controlPoints[1].y() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].y() + pow(u, 3) * controlPoints[3].y();
		float z = pow(1 - u, 3) * controlPoints[0].z() + 3 * pow(1 - u, 2) * u * controlPoints[1].z() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].z() + pow(u, 3) * controlPoints[3].z();

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		colors.push_back(0.0);
		colors.push_back(1.0);
		colors.push_back(0.0);

		if(i==2)
		{
			vertices.push_back(x);
			vertices.push_back(y + 4);
			vertices.push_back(z);

			colors.push_back(0.0);
			colors.push_back(1.0);
			colors.push_back(0.0);
		}
	}
}