#include "stdafx.h"
#include "Container.h"
using namespace DS;
//DS::Container DS::Container::*container = nullptr;
Container* Container::container = nullptr;
DS::Container::Container()
{
	mDefaultPoints.push_back(-1.5);
	mDefaultPoints.push_back(0.0);
	mDefaultPoints.push_back(0.0);

	mDefaultPoints.push_back(-0.5);
	mDefaultPoints.push_back(1.5);
	mDefaultPoints.push_back(0.0);

	mDefaultPoints.push_back(0.5);
	mDefaultPoints.push_back(-1.5);
	mDefaultPoints.push_back(0.0);

	mDefaultPoints.push_back(1.5);
	mDefaultPoints.push_back(0.0);
	mDefaultPoints.push_back(0.0);
}

Container::~Container() {
	// Add necessary cleanup code
	delete container;
}

DS::Container* DS::Container::getInstance()
{
	if (container == nullptr)
		container = new DS::Container();
	return container;
}

std::vector<GLdouble>  DS::Container::vertices()
{
	return mVertices;
}
std::vector<GLdouble> DS::Container::colors()
{
	return mColors;
}
std::vector<Geometry::Point3D> DS::Container::controlPoints()
{
	return mControlPoints;
}

std::vector<GLdouble> DS::Container::defaultPoints()
{
	return mDefaultPoints;
}

void DS::Container::setControlPoints(std::vector<Geometry::Point3D> points) {
	mControlPoints = points;

}

