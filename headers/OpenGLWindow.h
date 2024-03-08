#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Point3D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow();
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();
    std::vector<Geometry::Point3D> vertices();
    void displayBezierCurve(std::vector<Geometry::Point3D>& controlPoints);
    void bezierFuntionality();
    void bsplineFunctionality();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void zoomIn();
    void zoomOut();
   

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    std::vector<GLdouble> displayVertices;
    std::vector<GLdouble> displayColors;
    std::vector<Geometry::Point3D> mVertices;
    /*QList<QVector3D> mNormals;*/
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QQuaternion rotationAngle;
    QPoint lastPos;
    float scaleFactor = 1.0;

    int m_frame;
    GLdouble StartPtX;
    GLdouble StartPtY;
    GLdouble StartPtZ;
    GLdouble CrtlPt1X;
    GLdouble CrtlPt1Y;
    GLdouble CrtlPt1Z;
    GLdouble CrtlPt2X;
    GLdouble CrtlPt2Y;
    GLdouble CrtlPt2Z;
    GLdouble CrtlPt3X;
    GLdouble CrtlPt3Y;
    GLdouble CrtlPt3Z;
    GLdouble CrtlPt4X;
    GLdouble CrtlPt4Y;
    GLdouble CrtlPt4Z;
    GLdouble EndPtX;
    GLdouble EndPtY;
    GLdouble EndPtZ;
};