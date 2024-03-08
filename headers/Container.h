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
			std::vector<GLdouble> mVertices;
			std::vector<GLdouble> mColors;
			std::vector<GLdouble> mDefaultPoints;
			Container();
			static Container* container;
			~Container();
		
	public:
		static Container* getInstance();
		std::vector<GLdouble>  vertices();
		std::vector<GLdouble> colors();
		std::vector<GLdouble> defaultPoints();
		std::vector<Geometry::Point3D> controlPoints();
		void setControlPoints(std::vector<Geometry::Point3D>);

			//std::vector<GLdouble>vertices;


			//std::vector<GLdouble>vertices;

	};
}