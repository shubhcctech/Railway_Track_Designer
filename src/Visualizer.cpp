#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Bezier.h"
#include "BSpline.h"
#include "Container.h"
using namespace Geometry;



Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr),controlPoints(3), checked(false)
{
    setupUi();
}

Visualizer::~Visualizer()
{}
void Visualizer::setupUi()
{   

    DS::Container* containerInstance = DS::Container::getInstance();
   
    points.emplace_back(-1.5, 0, 0);
    points.emplace_back(-0.5, 1.5, 0);
    points.emplace_back(0.5, -1.5, 0);
    points.emplace_back(1.5, 0, 0);
    containerInstance->setControlPoints(points);

    ///Object Creation
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
    mSet = new QPushButton("Set", this);
    mGridLayout = new QGridLayout(mCentralWidget);
    mWidget = new QWidget(this);
    mGridLayout1 = new QGridLayout(mWidget);
    mRadioButton1 = new QRadioButton("Bezier", this);
    mRadioButton2 = new QRadioButton("B-Spline", this);
    mXcoordinate = new QDoubleSpinBox(this);
    mYcoordinate = new QDoubleSpinBox(this);
    mZcoordinate = new QDoubleSpinBox(this);
    mParameters = new QLabel("Parameters: ", this);
    mSelectedValuesLabel = new QLabel("Selected Values: Start Point", this);
    mComboBox = new QComboBox();
    mParameters->setFont(font);
    mSet->setFont(font);
    mRadioButton1->setFont(font);
    mRadioButton2->setFont(font);
    mSelectedValuesLabel->setFont(font);
    mButtonGroupForRadioBtn = new QButtonGroup(this);
    mButtonGroupForRadioBtn->addButton(mRadioButton1);
    mButtonGroupForRadioBtn->addButton(mRadioButton2);
    mRadioButton1->setChecked(true);
    mAddSpinBoxButton->setVisible(checked);

    /// Add list to Combo box.
    mComboBox->addItem("Start Point");
    mComboBox->addItem("End Point");
    mComboBox->addItem("Control Point 1");
    mComboBox->addItem("Control Point 2");

   /// Setting the spin boxes.
    mXcoordinate->setRange(-100.0, 100.0);
    mXcoordinate->setSingleStep(0.5);
    mXcoordinate->setPrefix("X: ");
    mXcoordinate->setValue(points[0].x());
    mYcoordinate->setRange(-100.0, 100.0);
    mYcoordinate->setSingleStep(0.5);
    mYcoordinate->setPrefix("Y: ");
    mYcoordinate->setValue(points[0].y());
    mZcoordinate->setRange(-100.0, 100.0);
    mZcoordinate->setSingleStep(0.5);
    mZcoordinate->setPrefix("Z: ");
    mZcoordinate->setValue(points[0].z());

    /// Button sizes
    mDisplay->setFixedHeight(50);
    

    /// Aligning the widgets into the layout
    mGridLayout->addWidget(mRenderer, 0, 0,10,4);
    mGridLayout->addWidget(mRenderer1, 0, 4, 10, 4);
    mGridLayout->addWidget(mRadioButton1, 0, 8, 1, 1);
    mGridLayout->addWidget(mRadioButton2, 0, 10, 1, 1);
    mGridLayout->addWidget(mParameters, 1, 8, 1, 3);
    mGridLayout->addWidget(mComboBox, 2, 8, 1, 3);
    mGridLayout->addWidget(mSelectedValuesLabel, 3, 8, 1, 3);
    mGridLayout->addWidget(mXcoordinate, 4, 8, 1, 1);
    mGridLayout->addWidget(mYcoordinate, 4, 9, 1, 1);
    mGridLayout->addWidget(mZcoordinate, 4, 10, 1, 1);
    mGridLayout->addWidget(mSet, 5, 8, 1, 3);
    mGridLayout->addWidget(mAddSpinBoxButton, 6, 8, 1, 3);
    mGridLayout->addWidget(mDisplay,9, 8, 1, 3);
   
   /* mPointsList = new QListWidget();
    mGridLayout->addWidget(mPointsList, 48, 6, 2, 3);*/

    /// Setting the components.
    setMenuBar(mMenuBar);
    addToolBar(mMainToolBar);
    setStatusBar(mStatusBar);
    setCentralWidget(mCentralWidget);
    setWindowTitle(QCoreApplication::translate("Railway Track Generator", "Railway Track Generator", nullptr));
 

    /// Connectors declared.
    connect(mDisplay, &QPushButton::clicked, this, &Visualizer::handleDisplayButtonClicked);
    connect(mAddSpinBoxButton, &QPushButton::clicked, this, &Visualizer::addSpinBox);
    connect(mRadioButton1, &QRadioButton::clicked, this, &Visualizer::handleRadioButtonClicked);
    connect(mRadioButton2, &QRadioButton::clicked, this, &Visualizer::handleRadioButtonClicked);
    connect(mSet, &QPushButton::clicked, this, &Visualizer::setPoints);
    connect(mComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Visualizer::updateSelectedValuesLabel);

}


///  Display Button.
void Visualizer::handleDisplayButtonClicked()
{
    
    if (checked) {
        
        bsplineCurveFunctionality();
        bsplineFunctionality();
    }
    else {
       bezierCurveFuntionality();
       bezierFuntionality();
    }
 
}

/// Function to add Spin boxes.
void Visualizer::addSpinBox()
{
    
    if (mComboBox) {
        ///  Add an item to the comboBox
        QString newItem = "Control Point "+QString::number(controlPoints);
        mComboBox->addItem(newItem);
        controlPoints++;
        
    }
    else {
        qDebug() << "QComboBox not initialized.";
    }
}
// Radio button handling
void Visualizer::handleRadioButtonClicked()
{
    if (mRadioButton1->isChecked()) {
        checked = false;
        mAddSpinBoxButton->setVisible(checked);
        mComboBox->clear();
        mComboBox->addItem("Start Point");
        mComboBox->addItem("End Point");
        mComboBox->addItem("Control Point 1");
        mComboBox->addItem("Control Point 2");


    }
    else if (mRadioButton2->isChecked()) {
        checked = true;
        mAddSpinBoxButton->setVisible(checked);
        mComboBox->clear();
        mComboBox->addItem("Start Point");
        mComboBox->addItem("End Point");
        for (int i = 1; i <= controlPoints - 1; ++i) {
            QString newItem = "Control Point " + QString::number(i);
            mComboBox->addItem(newItem);
        }
        
        // Set the combo box index to a valid value if it's out of bounds
        if (mComboBox->currentIndex() >= mComboBox->count()) {
            mComboBox->setCurrentIndex(0);
        }       
    }

}
void Visualizer::updateSelectedValuesLabel(int index)
{
    if (mComboBox) {
        QString selectedText = mComboBox->itemText(index);
        // You can modify this to display the actual values from your data structure
        mSelectedValuesLabel->setText("Selected Values: " + selectedText);
        if (index >= 0 && index < static_cast<int>(points.size())) {
                      
            mXcoordinate->setValue(points[index].x());
            mYcoordinate->setValue(points[index].y());
            mZcoordinate->setValue(points[index].z());
        }

    }
    else {
        qDebug() << "QComboBox not initialized.";
    }
}

void Visualizer::setPoints() {

    DS::Container* containerInstance = DS::Container::getInstance();
    containerInstance->controlPoints().clear();
    
    double xCoordinate = mXcoordinate->value();
    double yCoordinate = mYcoordinate->value();
    double zCoordinate = mZcoordinate->value();

    int selectedIndex = mComboBox->currentIndex();

    // Check if a valid item is selected in the combo box
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(points.size())) {
        // Modify the Y-coordinate of the selected point
        points[selectedIndex].setX(xCoordinate);
        points[selectedIndex].setY(yCoordinate);
        points[selectedIndex].setZ(zCoordinate);
        // Update the container with the modified control points
        containerInstance->setControlPoints(points);
    }
    else
    {
        points.emplace_back(xCoordinate, yCoordinate, zCoordinate);
        containerInstance->setControlPoints(points);
    }
    
}

void Visualizer::bezierFuntionality()
{
    OutputDebugStringA("Bezier clicked\n");

    ContainerData data;

    DS::Container* container = DS::Container::getInstance();

    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve(container->controlPoints(), data.mCurveVertices1, data.mCurveVertices2, data.mCurveVertices3, data.mCurveVertices4, data.mColors, 2, data.mCurveNormals1, data.mCurveNormals2, data.mCurveNormals3, data.mCurveNormals4);
    mRenderer1->setData(data);
    mRenderer1->update();

}

//left side
void Visualizer::bezierCurveFuntionality()
{
    OutputDebugStringA("Bezier curve\n");

    ContainerData data;

    DS::Container* container = DS::Container::getInstance();

    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve(container->controlPoints(), data.mCurveVertices1, data.mCurveVertices2, data.mCurveVertices3, data.mCurveVertices4, data.mColors, 1, data.mCurveNormals1, data.mCurveNormals2, data.mCurveNormals3, data.mCurveNormals4);
    mRenderer->setData(data);
    mRenderer->update();
}

void Visualizer::bsplineFunctionality()
{
    OutputDebugStringA("BSpline clicked\n");

    ContainerData data;
    DS::Container* container = DS::Container::getInstance();

    Feature::BSpline bsplineObj(container->controlPoints().size() - 1);
    bsplineObj.drawBsplineCurve(container->controlPoints(), data.mCurveVertices1, data.mCurveVertices2, data.mCurveVertices3, data.mCurveVertices4, data.mColors, 2);
    assignColors(container->controlPoints());

    mRenderer1->setData(data);
    mRenderer1->update();
}

void Visualizer::bsplineCurveFunctionality()
{
    OutputDebugStringA("BSpline clicked\n");

    ContainerData data;
    DS::Container* container = DS::Container::getInstance();

    Feature::BSpline bsplineObj(container->controlPoints().size() - 1);
    bsplineObj.drawBsplineCurve(container->controlPoints(), data.mCurveVertices1, data.mCurveVertices2, data.mCurveVertices3, data.mCurveVertices4, data.mColors, 1);
    assignColors(container->controlPoints());
    mRenderer->setData(data);
    mRenderer->update();
}

void Visualizer::assignColors(std::vector<Geometry::Point3D>& controlPoints)
{
    /*for (int i = 0; i < controlPoints.size(); i++)
    {
        displayControlPoints.push_back(controlPoints[i].x());
        displayControlPoints.push_back(controlPoints[i].y());
        displayControlPoints.push_back(controlPoints[i].z());

        displayControlColors.push_back(1);
        displayControlColors.push_back(0);
        displayControlColors.push_back(0);
    }*/
}



