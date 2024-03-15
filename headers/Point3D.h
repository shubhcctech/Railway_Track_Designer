#pragma once

namespace Geometry
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(double x, double y, double z);
        ~Point3D();
        double x() const;
        double y() const;
        double z() const;
        void setX(double value);
        void setY(double value);
        void setZ(double value);
    private:
        double mX;
        double mY;
        double mZ;
    };
}