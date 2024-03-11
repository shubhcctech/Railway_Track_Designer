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
<<<<<<< HEAD
        std::vector<Geometry::Point3D> evaluate1D(std::vector<Geometry::Point3D> control_points, float t);
        std::vector<Geometry::Point3D> evaluate2D(std::vector<Geometry::Point3D> control_points, float t);
        void drawBsplineCurve1D(std::vector<Geometry::Point3D>& control_points, std::vector<GLdouble>& inVertices, std::vector<GLdouble>& inColors);
        void drawBsplineCurve2D(std::vector<Geometry::Point3D>& control_points, std::vector<GLdouble>& inVertices, std::vector<GLdouble>& inColors);
=======
        std::vector<Geometry::Point3D> evaluate(std::vector<Geometry::Point3D> control_points, float t, int str);
        void drawBsplineCurve(std::vector<Geometry::Point3D>& control_points, std::vector<GLdouble>& inVertices, std::vector<GLdouble>& inColors,int str);
>>>>>>> c2919797ac1910363d74c081458f16265e052fa8

    private:
        int mDegree;
        std::vector<double> generateUniformKnots(int num_control_points);
        double bSplineBasis(int i, int k, float t, const std::vector<double>& knots);
    };
}

