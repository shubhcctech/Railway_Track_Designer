#include "stdafx.h"
#include "Bezier.h"
#include <cmath>

Feature::Bezier::Bezier()
{

}
Feature::Bezier::~Bezier()
{

}



void Feature::Bezier::drawCurve(std::vector<Geometry::Point3D>& controlPoints, std::vector<GLdouble>& curveVertices1, std::vector<GLdouble>& curveVertices2, std::vector<GLdouble>& curveVertices3, std::vector<GLdouble>& curveVertices4, std::vector<GLdouble>& colors, int i, std::vector<GLdouble> mCurveNormals1, std::vector<GLdouble> mCurveNormals2, std::vector<GLdouble> mCurveNormals3, std::vector<GLdouble> mCurveNormals4)

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

        float dx_du = -3 * pow(1 - u, 2) * controlPoints[0].x() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].x() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].x() + 3 * pow(u, 2) * controlPoints[3].x();

        float dy_du = -3 * pow(1 - u, 2) * controlPoints[0].y() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].y() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].y() + 3 * pow(u, 2) * controlPoints[3].y();

        float dz_du = -3 * pow(1 - u, 2) * controlPoints[0].z() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].z() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].z() + 3 * pow(u, 2) * controlPoints[3].z();

        // Calculate the length of the tangent vector

        float tangent_length = sqrt(dx_du * dx_du + dy_du * dy_du + dz_du * dz_du);

        // Normalize the tangent vector

        float tangent_x = dx_du / tangent_length;

        float tangent_y = dy_du / tangent_length;

        float tangent_z = dz_du / tangent_length;

        // Calculate the binormal vector (cross product of tangent with (0,1,0))

        float binormal_x = tangent_y * 0.0f - tangent_z * 1.0f;

        float binormal_y = tangent_z * 0.0f - tangent_x * 1.0f;

        float binormal_z = tangent_x * 1.0f - tangent_y * 0.0f;

        // Calculate the length of the binormal vector

        float binormal_length = sqrt(binormal_x * binormal_x + binormal_y * binormal_y + binormal_z * binormal_z);

        // Normalize the binormal vector

        binormal_x /= binormal_length;

        binormal_y /= binormal_length;

        binormal_z /= binormal_length;

        // Calculate the normal vector (cross product of tangent with binormal)

        float normal_x = tangent_y * binormal_z - tangent_z * binormal_y;

        float normal_y = tangent_z * binormal_x - tangent_x * binormal_z;

        float normal_z = tangent_x * binormal_y - tangent_y * binormal_x;

        // Normalize the normal vector

        float normal_length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);

        normal_x /= normal_length;

        normal_y /= normal_length;

        normal_z /= normal_length;

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

            float dx_du = -3 * pow(1 - u, 2) * controlPoints[0].x() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].x() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].x() + 3 * pow(u, 2) * controlPoints[3].x();

            float dy_du = -3 * pow(1 - u, 2) * controlPoints[0].y() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].y() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].y() + 3 * pow(u, 2) * controlPoints[3].y();

            float dz_du = -3 * pow(1 - u, 2) * controlPoints[0].z() + 3 * (pow(1 - u, 2) - 2 * (1 - u) * u) * controlPoints[1].z() + 3 * ((1 - u) * 2 * u - pow(u, 2)) * controlPoints[2].z() + 3 * pow(u, 2) * controlPoints[3].z();

            // Calculate the length of the tangent vector

            float tangent_length = sqrt(dx_du * dx_du + dy_du * dy_du + dz_du * dz_du);

            // Normalize the tangent vector

            float tangent_x = dx_du / tangent_length;

            float tangent_y = dy_du / tangent_length;

            float tangent_z = dz_du / tangent_length;

            // Calculate the binormal vector (cross product of tangent with (0,1,0))

            float binormal_x = tangent_y * 0.0f - tangent_z * 1.0f;

            float binormal_y = tangent_z * 0.0f - tangent_x * 1.0f;

            float binormal_z = tangent_x * 1.0f - tangent_y * 0.0f;

            // Calculate the length of the binormal vector

            float binormal_length = sqrt(binormal_x * binormal_x + binormal_y * binormal_y + binormal_z * binormal_z);

            // Normalize the binormal vector

            binormal_x /= binormal_length;

            binormal_y /= binormal_length;

            binormal_z /= binormal_length;

            // Calculate the normal vector (cross product of tangent with binormal)

            float normal_x = tangent_y * binormal_z - tangent_z * binormal_y;

            float normal_y = tangent_z * binormal_x - tangent_x * binormal_z;

            float normal_z = tangent_x * binormal_y - tangent_y * binormal_x;

            // Normalize the normal vector

            float normal_length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);

            normal_x /= normal_length;

            normal_y /= normal_length;

            normal_z /= normal_length;

            // Add the additional vertices and normals for lighting

            curveVertices1.push_back(x);

            curveVertices1.push_back(y + 4);

            curveVertices1.push_back(z);

            mCurveNormals1.push_back(normal_x);

            mCurveNormals1.push_back(normal_y);

            mCurveNormals1.push_back(normal_z);

            // Add the additional vertices and normals for lighting

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
