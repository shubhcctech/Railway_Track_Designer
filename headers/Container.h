#pragma once
#include "Point3D.h"
#include <vector>
#include <QOpenGLFunctions>

namespace DS
{
	class Container
	{
		
	public:
		static Container* getInstance();
		std::vector<Geometry::Point3D>& controlPoints();
		std::vector<GLdouble>& defaultPoints();
		void setControlPoints(std::vector<Geometry::Point3D>);
		std::vector<GLdouble>& curveNormals1();
		std::vector<GLdouble>& curveNormals2();
		std::vector<GLdouble>& curveNormals3();
		std::vector<GLdouble>& curveNormals4();
		std::vector<GLdouble>& curveVertices1();
		std::vector<GLdouble>& curveVertices2();
		std::vector<GLdouble>& curveVertices3();
		std::vector<GLdouble>& curveVertices4();
		std::vector<GLdouble>& colors();
	private:

		std::vector<Geometry::Point3D> mControlPoints;
		std::vector<GLdouble> mDefaultPoints;
		Container();
		static Container* container;
		~Container();
		std::vector<GLdouble> mCurveNormals1;
		std::vector<GLdouble> mCurveNormals2;
		std::vector<GLdouble> mCurveNormals3;
		std::vector<GLdouble> mCurveNormals4;
		std::vector<GLdouble> mCurveVertices1;
		std::vector<GLdouble> mCurveVertices2;
		std::vector<GLdouble> mCurveVertices3;
		std::vector<GLdouble> mCurveVertices4;
		std::vector<GLdouble> mColors;
			
	};
}