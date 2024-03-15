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

void OpenGLWindow::setData(ContainerData data) {
    mData = data;
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

    QMatrix4x4 modelMatrix;
    QMatrix4x4 translationMatrix;
    QMatrix4x4 scaleMatrix;
    QMatrix4x4 rotationMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;
    QMatrix3x3 normalMatrix;
    QVector3D lightPos;
    lightPos = QVector3D(0.0f, 5.0f, 20.0f);
    //projectionMatrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    projectionMatrix.perspective(60.0f * scaleFactor, 4.0f / 3.0f * scaleFactor, 0.1f, 100.0f);
    translationMatrix.translate(0, 0, -30);
    scaleMatrix.scale(2.0);
    rotationMatrix.rotate(rotationAngle);

    modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;
    viewMatrix.setToIdentity();
    normalMatrix = (modelMatrix.normalMatrix());

    mProgram->setUniformValue(m_modelMatrixUniform, modelMatrix);
    mProgram->setUniformValue(m_viewMatrixUniform, viewMatrix);
    mProgram->setUniformValue(m_projectionMatrixUniform, projectionMatrix);
    mProgram->setUniformValue(m_normalMatrixUniform, normalMatrix);
    mProgram->setUniformValue(m_lightPosUniform, lightPos);


    glLineWidth(3.0);



    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveVertices1.data());
    glVertexAttribPointer(m_normAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveNormals1.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mColors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
    glEnableVertexAttribArray(m_normAttr);


    glDrawArrays(GL_TRIANGLE_STRIP, 0, mData.mCurveVertices1.size() / 3);
    glDrawArrays(GL_LINE_STRIP, 0, mData.mColors.size() / 3);

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveVertices2.data());
    glVertexAttribPointer(m_normAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveNormals2.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mColors.data());




    glDrawArrays(GL_TRIANGLE_STRIP, 0, mData.mCurveVertices2.size() / 3);
    glDrawArrays(GL_LINE_STRIP, 0, mData.mColors.size() / 3);


    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveVertices3.data());
    glVertexAttribPointer(m_normAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveNormals3.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mColors.data());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, mData.mCurveVertices3.size() / 3);

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveVertices4.data());
    glVertexAttribPointer(m_normAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mCurveNormals4.data());
    glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, mData.mColors.data());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, mData.mCurveVertices4.size() / 3);

    //glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayControlPoints.data());
    //glVertexAttribPointer(m_colAttr, 3, GL_DOUBLE, GL_FALSE, 0, displayControlColors.data());

    //glEnableVertexAttribArray(m_posAttr);
    //glEnableVertexAttribArray(m_colAttr);


    /*glEnable(GL_PROGRAM_POINT_SIZE);

    glDrawArrays(GL_POINTS, 0, displayControlPoints.size()/3);*/

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}


void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        /*"attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_PointSize = 10.0;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";*/
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "attribute lowp vec3 norAttr;\n"
        "varying lowp vec4 col;\n"
        "varying vec3 vert;\n"
        "varying vec3 vertNormal;\n"
        "uniform highp mat4 projMatrix;\n"
        "uniform highp mat4 viewMatrix;\n"
        "uniform highp mat4 modelMatrix;\n"
        "uniform mat3 normalMatrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   vert = posAttr.xyz;\n"
        "   vertNormal = normalMatrix * norAttr;\n"
        "   gl_Position = projMatrix * viewMatrix * modelMatrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        /*"varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";*/
        "varying lowp vec4 col;\n"
        "varying highp vec3 vert;\n"
        "varying highp vec3 vertNormal;\n"
        "uniform highp vec3 lightPos;\n"
        "void main() {\n"
        "   highp vec3 L = normalize(lightPos - vert);\n"
        "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
        "   highp vec3 color = vec3(col);\n"
        "   highp vec3 col1 = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
        "   gl_FragColor = vec4(col1, 1.0);\n"
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
    m_normAttr = mProgram->attributeLocation("norAttr");
    Q_ASSERT(m_normAttr != -1);
    m_modelMatrixUniform = mProgram->uniformLocation("modelMatrix");
    Q_ASSERT(m_modelMatrixUniform != -1);
    m_viewMatrixUniform = mProgram->uniformLocation("viewMatrix");
    Q_ASSERT(m_viewMatrixUniform != -1);
    m_projectionMatrixUniform = mProgram->uniformLocation("projMatrix");
    Q_ASSERT(m_projectionMatrixUniform != -1);
    m_normalMatrixUniform = mProgram->uniformLocation("normalMatrix");
    Q_ASSERT(m_normalMatrixUniform != -1);
    m_lightPosUniform = mProgram->uniformLocation("lightPos");
    Q_ASSERT(m_lightPosUniform != -1);
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

