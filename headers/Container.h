#pragma once
#include "Point3D.h"
#include <vector>
#include <QOpenGLFunctions>

namespace DS
{
	class Container
	{
		private:

			std::vector<Geometry::Point3D> mControlPoints;
			std::vector<GLdouble> mCurveVertices1;
			std::vector<GLdouble> mCurveVertices2;
			std::vector<GLdouble> mCurveVertices3;
			std::vector<GLdouble> mCurveVertices4;
			std::vector<GLdouble> mColors;
			std::vector<GLdouble> mDefaultPoints;
			Container();
			static Container* container;
			~Container();
		
	public:
		static Container* getInstance();
		std::vector<GLdouble>  curveVertices1();
		std::vector<GLdouble>  curveVertices2();
		std::vector<GLdouble>  curveVertices3();
		std::vector<GLdouble>  curveVertices4();
		std::vector<GLdouble> colors();
		std::vector<GLdouble> defaultPoints();
		std::vector<Geometry::Point3D> controlPoints();
		void setControlPoints(std::vector<Geometry::Point3D>);

			
	};
}