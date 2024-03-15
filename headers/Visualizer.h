#pragma once
#include"Point3D.h"
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
using namespace Geometry;
class OpenGLWindow;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();
    //void handleSpinBoxValueChanged(double value);
    void handleDisplayButtonClicked();
    void addSpinBox();
    void handleRadioButtonClicked();
    void updatePointLabelText(int index);
    void updateSelectedValuesLabel(int index);
    void setPoints();
    void bezierFuntionality();
    void bezierCurveFuntionality();
    void bsplineFunctionality();
    void bsplineCurveFunctionality();
    void assignColors(std::vector<Geometry::Point3D>& controlPoints);
private:
    int controlPoints;
    int row;
    bool checked;
    QListWidget* mPointsList;
    
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QWidget* mWidget;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;
    OpenGLWindow* mRenderer1;
    QGridLayout* mGridLayout;
    QGridLayout* mGridLayout1;
    QPushButton* mDisplay;
    QPushButton* mAddSpinBoxButton;
    QPushButton* mSet;
    QRadioButton* mRadioButton1;
    QRadioButton* mRadioButton2;
    QButtonGroup* mButtonGroupForRadioBtn;
    QDoubleSpinBox* mXcoordinate;
    QDoubleSpinBox* mYcoordinate;
    QDoubleSpinBox* mZcoordinate;
    QLabel* mParameters;
    QLabel* mPoint;
    QLabel* mSelectedValuesLabel;
    std::vector<Point3D> points;
    QComboBox* mComboBox;
    
};