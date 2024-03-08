#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Bezier.h"
#include "Container.h"
using namespace Geometry;



Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr), row(17), checked(false)
{
	setupUi();
}

Visualizer::~Visualizer()
{}
void Visualizer::setupUi()
{

	DS::Container* containerInstance = DS::Container::getInstance();
	std::vector<GLdouble> defaultPoints = containerInstance->defaultPoints();

	// Label declaration
	QString labels[] = { "X: ", "Y: ", "Z: ", "X: ", "Y: ", "Z: ", "X: ", "Y: ", "Z: ", "X: ", "Y: ", "Z: " };
	QString textLabels[] = { "Start Point:","End Point:","Control Point 1:","Control Point 2:" };
	// Object Creaion
	QFont font;
	font.setBold(true);
	QSize buttonSize = QSize(200, 50);
	QSize spinSize = QSize(60, 40);
	resize(600, 600);
	mDisplay = new QPushButton("DISPLAY", this);
	mAddSpinBoxButton = new QPushButton("Add Control Point", this);
	mDisplay->setFont(font);
	mAddSpinBoxButton->setFont(font);
	mMenuBar = new QMenuBar(this);
	mMainToolBar = new QToolBar(this);
	mStatusBar = new QStatusBar(this);
	mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
	mRenderer1 = new OpenGLWindow(QColor(9, 9, 9), this);
	mCentralWidget = new QWidget(this);
	mGridLayout = new QGridLayout(mCentralWidget);
	mWidget = new QWidget(this);
	mGridLayout1 = new QGridLayout(mWidget);
	mRadioButton1 = new QRadioButton("Bezier", this);
	mRadioButton2 = new QRadioButton("B-Spline", this);
	mRadioButton1->setFont(font);
	mRadioButton2->setFont(font);
	mButtonGroupForRadioBtn = new QButtonGroup(this);
	mButtonGroupForRadioBtn->addButton(mRadioButton1);
	mButtonGroupForRadioBtn->addButton(mRadioButton2);
	mRadioButton1->setChecked(true);



	//Created Spin box
	mSpinBoxArray.resize(12);
	int count = 0;
	for (int i = 0; i < 4; i++) {
		QLabel* textLabel = new QLabel(textLabels[i], this);
		textLabel->setFixedWidth(100);
		textLabel->setFont(font);
		mGridLayout1->addWidget(textLabel, i + 1, 0);
		for (int j = 0; j < 3; j++) {
			if (count < mSpinBoxArray.size()) {
				mSpinBoxArray[count] = new QDoubleSpinBox(this);
				mSpinBoxArray[count]->setRange(-100.0, 100.0);
				mSpinBoxArray[count]->setSingleStep(0.5);
				mSpinBoxArray[count]->setPrefix(labels[count]);
				mSpinBoxArray[count]->setValue(defaultPoints[count]);
				mGridLayout1->addWidget(mSpinBoxArray[count], i + 1, j + 1, 1, 1);
				count++;

			}
		}
	}


	//Button sizes
	mDisplay->setFixedHeight(50);
	mAddSpinBoxButton->setFixedHeight(50);

	// Aligning the widgets into the layout
	mGridLayout1->addWidget(mDisplay, row + 2, 0, 1, 0);
	mGridLayout1->addWidget(mAddSpinBoxButton, row + 3, 0, 1, 0);
	mGridLayout1->addWidget(mRadioButton1, 0, 0, 1, 0);
	mGridLayout1->addWidget(mRadioButton2, 0, 1, 1, 1);
	mGridLayout->addWidget(mRenderer, 0, 2, 1, 1);
	mGridLayout->addWidget(mRenderer1, 0, 5, 1, 1);
	mGridLayout->addWidget(mWidget, 0, 6, 1, 1);
	mGridLayout->setSpacing(20);
	mGridLayout->addWidget(mWidget, 0, 6, 1, 1);



	//Setting the components
	setMenuBar(mMenuBar);
	addToolBar(mMainToolBar);
	setStatusBar(mStatusBar);
	setCentralWidget(mCentralWidget);
	setWindowTitle(QCoreApplication::translate("Railway Track Generator", "Railway Track Generator", nullptr));


	//Connectors declared
	connect(mDisplay, &QPushButton::clicked, this, &Visualizer::handleDisplayButtonClicked);
	connect(mAddSpinBoxButton, &QPushButton::clicked, this, &Visualizer::addSpinBox);
	connect(mRadioButton1, &QRadioButton::clicked, this, &Visualizer::handleRadioButtonClicked);
	connect(mRadioButton2, &QRadioButton::clicked, this, &Visualizer::handleRadioButtonClicked);

}

void Visualizer::handleDisplayButtonClicked()
{
	
	DS::Container* container = DS::Container::getInstance();
	std::vector<Point3D> controlPoints;


	for (int i = 0; i < 12; i += 3) {
		double xCoordinate;
		double yCoordinate;
		double zCoordinate;

		xCoordinate = mSpinBoxArray[i]->value();
		yCoordinate = mSpinBoxArray[i + 1]->value();
		zCoordinate = mSpinBoxArray[i + 2]->value();
		controlPoints.push_back(Geometry::Point3D(xCoordinate, yCoordinate, zCoordinate));
	}

	container->setControlPoints(controlPoints);

	if (checked) {
		//OutputDebugStringA("if\n");
		mRenderer->bsplineFunctionality1D();
		mRenderer1->bsplineFunctionality2D();
		mRenderer->update();
		mRenderer1->update();
	}

	else {
		//OutputDebugStringA("else\n"); // control will first move here : checked=false
		mRenderer->bezierFuntionality1D();
		mRenderer1->bezierFuntionality2D();
		mRenderer->update();
		mRenderer1->update();
	}

}

//Function to add Spin boxes.
void Visualizer::addSpinBox()
{

	QString labels[] = { "X: ", "Y: ", "Z: " };
	QFont font;
	font.setBold(true);
	int count = 3;
	// Create a new QDoubleSpinBox
	QDoubleSpinBox* mNewSpinBox = new QDoubleSpinBox(this);
	mNewSpinBox->setRange(-100.0, 100.0);
	mNewSpinBox->setSingleStep(0.5);
	mNewSpinBox->setValue(0.0);

	// Add the new QDoubleSpinBox to the layout
	row = mGridLayout1->rowCount();
	mGridLayout1->addWidget(mDisplay, row + 2, 0, 1, 0);
	mGridLayout1->addWidget(mAddSpinBoxButton, row + 3, 0, 1, 0);


	for (int i = 0; i < 4; i++) {
		QLabel* textLabel = new QLabel("New Control Pt", this);
		textLabel->setFixedWidth(100);
		textLabel->setFont(font);
		mGridLayout1->addWidget(textLabel, row + 1, 0);
		for (int j = 0; j < 3; j++) {
			if (count < mSpinBoxArray.size()) {
				mSpinBoxArray[count] = new QDoubleSpinBox(this);
				mSpinBoxArray[count]->setRange(-100.0, 100.0);
				mSpinBoxArray[count]->setSingleStep(0.5);
				mSpinBoxArray[count]->setPrefix(labels[j]);
				mSpinBoxArray[count]->setValue(0.0);
				mGridLayout1->addWidget(mSpinBoxArray[count], row + 1, j + 1, 1, 1);
				count++;
			}
		}
	}


	mSpinBoxArray.append(mNewSpinBox);
}
void Visualizer::handleRadioButtonClicked()
{
	if (mRadioButton1->isChecked()) {

		checked = false;
		/* mRenderer->bezierFuntionality();
		 mRenderer1->bezierFuntionality();
		 mRenderer->update();
		 mRenderer1->update();*/
	}
	else if (mRadioButton2->isChecked()) {

		checked = true;
		/* mRenderer->bsplineFunctionality();
		 mRenderer1->bsplineFunctionality();
		 mRenderer->update();
		 mRenderer1->update();*/
	}
}



