#pragma once
#pragma once
#pragma once
#include "Point3D.h"
#include <iostream>
#include <vector>
#include <QtWidgets>

namespace Feature
{
    class BSpline {

    public:
        BSpline(int degree);
        ~BSpline();
        std::vector<Geometry::Point3D> evaluate(std::vector<Geometry::Point3D> control_points, float t, int str);
        void drawBsplineCurve(std::vector<Geometry::Point3D>& control_points, std::vector<GLdouble>& curveVertices1, std::vector<GLdouble>& curveVertices2, std::vector<GLdouble>& curveVertices3, std::vector<GLdouble>& curveVertices4, std::vector<GLdouble>& inColors,int str);

    private:
        int mDegree;
        std::vector<double> generateUniformKnots(int num_control_points);
        double bSplineBasis(int i, int k, float t, const std::vector<double>& knots);
    };
}

