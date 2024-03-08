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

    glLineWidth(3.0);

    glDrawArrays(GL_LINE_STRIP, 0, displayVertices.size() / 3);
    
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
void OpenGLWindow::bezierFuntionality1D()
{    
    DS::Container* container = DS::Container::getInstance();
    std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    container->vertices().clear();
    container->colors().clear();

    displayVertices = container->vertices();
    displayColors = container->colors();

    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve1D(controlPoints, displayVertices, displayColors);
}

void OpenGLWindow::bezierFuntionality2D()
{
    DS::Container* container = DS::Container::getInstance();
    std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    container->vertices().clear();
    container->colors().clear();

    displayVertices = container->vertices();
    displayColors = container->colors();

    Feature::Bezier bzeierObj;
    bzeierObj.drawCurve2D(controlPoints, displayVertices, displayColors);
}


void OpenGLWindow::bsplineFunctionality1D()
{
    DS::Container* container = DS::Container::getInstance();
    std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();
    
    displayVertices = container->vertices();
    displayColors = container->colors();

    Feature::BSpline bsplineObj(3);
    bsplineObj.drawBsplineCurve1D(controlPoints, displayVertices, displayColors);
}

void OpenGLWindow::bsplineFunctionality2D()
{
    DS::Container* container = DS::Container::getInstance();
    std::vector<GLdouble> defaultVertices = container->defaultPoints();
    std::vector<Geometry::Point3D> controlPoints = container->controlPoints();

    displayVertices = container->vertices();
    displayColors = container->colors();

    Feature::BSpline bsplineObj(3);
    bsplineObj.drawBsplineCurve2D(controlPoints, displayVertices, displayColors);
}