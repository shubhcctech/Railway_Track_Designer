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
			std::vector<GLdouble> mDefaultPoints;
			Container();
			static Container* container;
			~Container();
		
	public:
		static Container* getInstance();
		std::vector<Geometry::Point3D>& controlPoints();
		std::vector<GLdouble>& defaultPoints();
		void setControlPoints(std::vector<Geometry::Point3D>);

			
	};
}