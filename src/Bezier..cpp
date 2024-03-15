#include "stdafx.h"
#include "Bezier.h"
#include <cmath>

Feature::Bezier::Bezier()
{

}
Feature::Bezier::~Bezier()
{

}

void Feature::Bezier::drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& curveVertices1, std::vector<GLdouble>& curveVertices2, std::vector<GLdouble>& curveVertices3, std::vector<GLdouble>& curveVertices4, std::vector<GLdouble>& colors, int i, std::vector<GLdouble> mCurveNormals1, std::vector<GLdouble> mCurveNormals2,std::vector<GLdouble> mCurveNormals3,std::vector<GLdouble> mCurveNormals4)
{
    for (float u = 0; u <= 1; u += 0.001)
    {
        // Calculate the position on the curve
        float x = pow(1 - u, 3) * controlPoints[0].x() + 3 * pow(1 - u, 2) * u * controlPoints[1].x() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].x() + pow(u, 3) * controlPoints[3].x();
        float y = pow(1 - u, 3) * controlPoints[0].y() + 3 * pow(1 - u, 2) * u * controlPoints[1].y() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].y() + pow(u, 3) * controlPoints[3].y();
        float z = pow(1 - u, 3) * controlPoints[0].z() + 3 * pow(1 - u, 2) * u * controlPoints[1].z() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].z() + pow(u, 3) * controlPoints[3].z();

        // Store the vertex position
        curveVertices1.push_back(x);
        curveVertices1.push_back(y);
        curveVertices1.push_back(z);

        // Calculate the tangent vector
        float tangent_x = -3 * pow(1 - u, 2) * controlPoints[0].x() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].x() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].x() + 3 * pow(u, 2) * controlPoints[3].x();
        float tangent_y = -3 * pow(1 - u, 2) * controlPoints[0].y() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].y() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].y() + 3 * pow(u, 2) * controlPoints[3].y();
        float tangent_z = -3 * pow(1 - u, 2) * controlPoints[0].z() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].z() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].z() + 3 * pow(u, 2) * controlPoints[3].z();

        // Calculate the normal vector (cross product of tangent with (0,0,1))
        float normal_x = tangent_y;
        float normal_y = -tangent_x;
        float normal_z = 0;

        // Normalize the normal vector
        float length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
        if (length != 0) {
            normal_x /= length;
            normal_y /= length;
            normal_z /= length;
        }

        // Add the normal vector to the vertex data
        mCurveNormals1.push_back(normal_x);
        mCurveNormals1.push_back(normal_y);
        mCurveNormals1.push_back(normal_z);

        // Set color for the vertex
        colors.push_back(0.0);
        colors.push_back(1.0);
        colors.push_back(0.0);

        // Additional vertices and normals for lighting if i == 2
        if (i == 2)
        {
            // Calculate the position on the curve
            float x = pow(1 - u, 3) * controlPoints[0].x() + 3 * pow(1 - u, 2) * u * controlPoints[1].x() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].x() + pow(u, 3) * controlPoints[3].x();
            float y = pow(1 - u, 3) * controlPoints[0].y() + 3 * pow(1 - u, 2) * u * controlPoints[1].y() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].y() + pow(u, 3) * controlPoints[3].y();
            float z = pow(1 - u, 3) * controlPoints[0].z() + 3 * pow(1 - u, 2) * u * controlPoints[1].z() + 3 * (1 - u) * pow(u, 2) * controlPoints[2].z() + pow(u, 3) * controlPoints[3].z();

            // Calculate the tangent vector
            float tangent_x = -3 * pow(1 - u, 2) * controlPoints[0].x() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].x() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].x() + 3 * pow(u, 2) * controlPoints[3].x();
            float tangent_y = -3 * pow(1 - u, 2) * controlPoints[0].y() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].y() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].y() + 3 * pow(u, 2) * controlPoints[3].y();
            float tangent_z = -3 * pow(1 - u, 2) * controlPoints[0].z() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].z() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].z() + 3 * pow(u, 2) * controlPoints[3].z();

            // Calculate the normal vector (cross product of tangent with (0,0,1))
            float normal_x = tangent_y;
            float normal_y = -tangent_x;
            float normal_z = 0;

            // Normalize the normal vector
            float length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
            if (length != 0) {
                normal_x /= length;
                normal_y /= length;
                normal_z /= length;
            }

            // Add the additional vertices and normals for lighting
            curveVertices1.push_back(x);
            curveVertices1.push_back(y + 4);
            curveVertices1.push_back(z);
            mCurveNormals1.push_back(normal_x);
            mCurveNormals1.push_back(normal_y);
            mCurveNormals1.push_back(normal_z);

            curveVertices2.push_back(x);
            curveVertices2.push_back(y + 4);
            curveVertices2.push_back(z);
            mCurveNormals2.push_back(normal_x);
            mCurveNormals2.push_back(normal_y);
            mCurveNormals2.push_back(normal_z);

            curveVertices2.push_back(x);
            curveVertices2.push_back(y + 4);
            curveVertices2.push_back(z - 4);
            mCurveNormals2.push_back(normal_x);
            mCurveNormals2.push_back(normal_y);
            mCurveNormals2.push_back(normal_z);

            curveVertices3.push_back(x);
            curveVertices3.push_back(y + 4);
            curveVertices3.push_back(z - 4);
            mCurveNormals3.push_back(normal_x);
            mCurveNormals3.push_back(normal_y);
            mCurveNormals3.push_back(normal_z);

            curveVertices3.push_back(x);
            curveVertices3.push_back(y);
            curveVertices3.push_back(z - 4);
            mCurveNormals3.push_back(normal_x);
            mCurveNormals3.push_back(normal_y);
            mCurveNormals3.push_back(normal_z);

            curveVertices4.push_back(x);
            curveVertices4.push_back(y);
            curveVertices4.push_back(z - 4);
            mCurveNormals4.push_back(normal_x);
            mCurveNormals4.push_back(normal_y);
            mCurveNormals4.push_back(normal_z);

            curveVertices4.push_back(x);
            curveVertices4.push_back(y);
            curveVertices4.push_back(z);
            mCurveNormals4.push_back(normal_x);
            mCurveNormals4.push_back(normal_y);
            mCurveNormals4.push_back(normal_z);

            // Set color for the vertices
            colors.push_back(0.0);
            colors.push_back(1.0);
            colors.push_back(0.0);
        }
    }
}
