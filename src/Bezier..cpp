#include "stdafx.h"
#include "Bezier.h"
#include <cmath>

Feature::Bezier::Bezier()
{

}
Feature::Bezier::~Bezier()
{

}
Geometry::Point3D Feature::Bezier::calculateBezierPoint(std::vector<Geometry::Point3D>& controlPoints, double t) {
	int n = 3;
	double x = 0.0, y = 0.0, z = 0.0;
	for (int i = 0; i <= n; ++i) {
		double binomialCoefficient = 1.0;
		for (int j = 0; j < i; ++j) {
			binomialCoefficient *= (n - j) / (j + 1.0);
		}

		double term = binomialCoefficient * pow(1 - t, n - i) * pow(t, i);
		x += controlPoints[i].x() * term;
		y += controlPoints[i].y() * term;
		z += controlPoints[i].z() * term;
	}
	return Geometry::Point3D(x, y, z);
}

void Feature::Bezier::drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& vertices, std::vector<GLdouble>& colors, int i)
{
	for (double t = 0; t <= 1; t += 0.001)
	{
		Geometry::Point3D bezierPoint = calculateBezierPoint(controlPoints, t);
		vertices.push_back(bezierPoint.x());
		vertices.push_back(bezierPoint.y());
		vertices.push_back(bezierPoint.z());

		colors.push_back(0.0);
		colors.push_back(1.0);
		colors.push_back(0.0);

		if(i==2)
		{
			vertices.push_back(bezierPoint.x());
			vertices.push_back(bezierPoint.y() + 4);
			vertices.push_back(bezierPoint.z());

			colors.push_back(0.0);
			colors.push_back(1.0);
			colors.push_back(0.0);
		}
	}

}