#include "stdafx.h"
#include "OpenGLWindow.h"
#include "Bezier.h"
#include "BSpline.h"
#include "Point3D.h"
#include "Container.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>

OpenGLWindow::OpenGLWindow() {

}
OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    //matrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);
    matrix.perspective(60.0f * scaleFactor, 4.0f / 3.0f * scaleFactor, 0.1f, 100.0f);
    matrix.translate(0, 0, -15);
    matrix.rotate(rotationAngle);
   
    mProgram->setUniformValue(m_matrixUniform, matrix);
    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayVertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayColors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);


    //glPointSize(1.0);
    glLineWidth(3.0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, displayVertices.size() / 3);
    glDrawArrays(GL_LINE_STRIP, 0, displayVertices.size() / 3);

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayControlPoints.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayControlColors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);


    glEnable(GL_PROGRAM_POINT_SIZE);

    glDrawArrays(GL_POINTS, 0, displayControlPoints.size());

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}


void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_PointSize = 10.0;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";
    rotationAngle = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.0f);
    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    glEnable(GL_DEPTH_TEST);

}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    }
}

void OpenGLWindow::zoomIn()
{
    scaleFactor /= 0.001f;
    update();
}

void OpenGLWindow::zoomOut()
{
    scaleFactor *= 0.001f;
    update();
}
std::vector<Geometry::Point3D> OpenGLWindow::vertices() {

    return mVertices;

}
void OpenGLWindow::displayBezierCurve(std::vector<Geometry::Point3D>& controlPoints) {

    DS::Container* container = DS::Container::getInstance();

    std::vector<Geometry::Point3D> controlPoint1 = controlPoints;
    displayVertices = container->vertices();
    displayColors = container->colors();

    Feature::Bezier bzeierObj;
   // bzeierObj.drawCurve(controlPoint1, displayVertices, displayColors);


}
void OpenGLWindow::bezierFuntionality()
{
    OutputDebugStringA("Bezier clicked\n");

    DS::Container* container = DS::Container::getInstance();
    displayControlPoints.clear();
    displayControlColors.clear();
    displayVertices.clear();
    displayColors.clear();
    //std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    
    displayVertices = container->vertices();
    displayColors = container->colors();
    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve(controlPoints, displayVertices, displayColors,2);
    assignColors(controlPoints);
}

void OpenGLWindow::bezierCurveFuntionality()
{  
    OutputDebugStringA("Bezier clicked1\n");

    DS::Container* container = DS::Container::getInstance();
    displayControlPoints.clear();
    displayControlColors.clear();
    displayVertices.clear();
    displayColors.clear();
    std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    
    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve(controlPoints, displayVertices, displayColors,1);
    assignColors(controlPoints);
}

void OpenGLWindow::bsplineFunctionality()
{
    OutputDebugStringA("BSpline clicked\n");

    DS::Container* container = DS::Container::getInstance();
    displayControlPoints.clear();
    displayControlColors.clear();
    displayVertices.clear();
    displayColors.clear();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    
    Feature::BSpline bsplineObj(3);
    bsplineObj.drawBsplineCurve(controlPoints, displayVertices, displayColors,2);
    assignColors(controlPoints);
}

void OpenGLWindow::bsplineCurveFunctionality()
{
    OutputDebugStringA("BSpline clicked\n");

    DS::Container* container = DS::Container::getInstance();
    displayControlPoints.clear();
    displayControlColors.clear();
    displayVertices.clear();
    displayColors.clear();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    
    Feature::BSpline bsplineObj(controlPoints.size());
    bsplineObj.drawBsplineCurve(controlPoints, displayVertices, displayColors, 1);
    assignColors(controlPoints);
}

void OpenGLWindow::assignColors(std::vector<Geometry::Point3D>& controlPoints)
{
    for (int i = 0; i < controlPoints.size(); i++)
    {
        displayControlPoints.push_back(controlPoints[i].x());
        displayControlPoints.push_back(controlPoints[i].y());
        displayControlPoints.push_back(controlPoints[i].z());

        displayControlColors.push_back(1);
        displayControlColors.push_back(0);
        displayControlColors.push_back(0);
    }
}