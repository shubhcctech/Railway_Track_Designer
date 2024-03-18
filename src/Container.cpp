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

std::vector<Geometry::Point3D>& DS::Container::controlPoints()
{
	return mControlPoints;
}

std::vector<GLdouble>& DS::Container::defaultPoints()
{
	return mDefaultPoints;
}

void DS::Container::setControlPoints(std::vector<Geometry::Point3D> points) {
	mControlPoints = points;

}

std::vector<GLdouble>& DS::Container::curveNormals1()
{
	return mCurveNormals1;
}
std::vector<GLdouble>& DS::Container::curveNormals2()
{
	return mCurveNormals2;
}
std::vector<GLdouble>& DS::Container::curveNormals3()
{
	return mCurveNormals3;

}
std::vector<GLdouble>& DS::Container::curveNormals4()
{
	return mCurveNormals4;

}
std::vector<GLdouble>& DS::Container::curveVertices1()
{
	return mCurveVertices1;
}
std::vector<GLdouble>& DS::Container::curveVertices2()
{
	return mCurveVertices2;
}
std::vector<GLdouble>& DS::Container::curveVertices3()
{
	return mCurveVertices3;
}
std::vector<GLdouble>& DS::Container::curveVertices4()
{
	return mCurveVertices4;
}
