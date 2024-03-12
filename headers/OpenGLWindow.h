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
    void bezierCurveFuntionality();
    void bsplineFunctionality();
    void bsplineCurveFunctionality();
    void assignColors(std::vector<Geometry::Point3D>& controlPoints);
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
    std::vector<GLdouble> displayControlPoints;
    std::vector<GLdouble> displayControlColors;
    std::vector<Geometry::Point3D> mVertices;
    std::vector<GLdouble> mCurveVertices1;
    std::vector<GLdouble> mCurveVertices2;
    std::vector<GLdouble> mCurveVertices3;
    std::vector<GLdouble> mCurveVertices4;
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
    
};