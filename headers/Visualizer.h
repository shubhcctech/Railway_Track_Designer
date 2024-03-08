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
    void handleSpinBoxValueChanged(double value);
    void handleDisplayButtonClicked();
    void addSpinBox();
    void handleRadioButtonClicked();

private:
    int row;
    bool checked;
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
    QRadioButton* mRadioButton1;
    QRadioButton* mRadioButton2;
    QButtonGroup* mButtonGroupForRadioBtn;
    QVector<QDoubleSpinBox*> mSpinBoxArray;
    std::vector<Point3D> points;
    
};