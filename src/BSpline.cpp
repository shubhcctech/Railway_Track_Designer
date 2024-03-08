#include "stdafx.h"
#include "BSpine.h"

Feature::BSpline::BSpline(int degree) :mDegree(degree)
{
}

Feature::BSpline::~BSpline()
{

}

// B-spline basis function
std::vector<double> Feature::BSpline::generateUniformKnots(int num_control_points) {
    int num_knots = num_control_points + mDegree + 1;
    std::vector<double> knots(num_knots);

    // Assign the first 'degree + 1' knots as 0
    for (int i = 0; i <= mDegree; ++i) {
        knots[i] = 0.0f;
    }

    // Assign the last 'degree + 1' knots as 1
    for (int i = num_knots - mDegree - 1; i < num_knots; ++i) {
        knots[i] = 1.0f;
    }

    // Calculate internal knots
    for (int i = mDegree + 1; i < num_control_points; ++i) {
        knots[i] = static_cast<double>(i - mDegree) / (num_control_points - mDegree);
    }

    return knots;
}
double Feature::BSpline::bSplineBasis(int i, int k, float t, const std::vector<double>& knots) {
    if (k == 1) {
        if (knots[i] <= t && t < knots[i + 1]) {
            return 1.0f;
        }
        return 0.0f;
    }

    double denom1 = knots[i + k - 1] - knots[i];
    double denom2 = knots[i + k] - knots[i + 1];

    double c1 = (denom1 != 0.0f) ? ((t - knots[i]) / denom1 * bSplineBasis(i, k - 1, t, knots)) : 0.0f;
    double c2 = (denom2 != 0.0f) ? ((knots[i + k] - t) / denom2 * bSplineBasis(i + 1, k - 1, t, knots)) : 0.0f;

    return c1 + c2;
}

std::vector<Geometry::Point3D> Feature::BSpline::evaluate(std::vector<Geometry::Point3D> control_points, float t) {
    int num_control_points = control_points.size();
    std::vector<double> knots = generateUniformKnots(num_control_points);

    std::vector<Geometry::Point3D> curve_points;

    // Calculate the step size based on the number of samples
    float step = 1.0f / static_cast<float>(t - 1);

    for (int i = 0; i < t; ++i) {
        float t = static_cast<float>(i) * step; // Calculate the parameter 't' within the range [0, 1]
        Geometry::Point3D curve_point(0.0, 0.0, 0.0); // Initialize curve_point for this iteration
        Geometry::Point3D curve_point1(0.0, 0.0, 0.0);
        for (int j = 0; j < num_control_points; ++j) {
            float basis = bSplineBasis(j, mDegree + 1, t, knots);
            curve_point.setX(curve_point.x() + control_points.at(j).x() * basis);
            curve_point.setY(curve_point.y() + control_points.at(j).y() * basis);
            curve_point.setZ(curve_point.z() + control_points.at(j).z() * basis);


            curve_point1.setX(curve_point.x() + control_points.at(j).x() * basis);
            curve_point1.setY((curve_point.y() + control_points.at(j).y() * basis) + 4);
            curve_point1.setZ(curve_point.z() + control_points.at(j).z() * basis);
        }
        curve_points.push_back(curve_point); // Store the computed point
        curve_points.push_back(curve_point1);
    }
    curve_points.pop_back();
    curve_points.pop_back();
    return curve_points;
}

void Feature::BSpline::drawBsplineCurve(std::vector<Geometry::Point3D>& control_points, std::vector<GLdouble>& inVertices, std::vector<GLdouble>& inColors)
{
    std::vector<Geometry::Point3D> curve_points = evaluate(control_points, 100);
    for (Geometry::Point3D point : curve_points)
    {
        inVertices.push_back(point.x());
        inVertices.push_back(point.y());
        inVertices.push_back(point.z());

        inColors.push_back(0.5);
        inColors.push_back(0.5);
        inColors.push_back(0.5);
    }
}