#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Point3D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

struct ContainerData
{
    std::vector<GLdouble> mCurveNormals1;
    std::vector<GLdouble> mCurveNormals2;
    std::vector<GLdouble> mCurveNormals3;
    std::vector<GLdouble> mCurveNormals4;
    std::vector<GLdouble> mCurveVertices1;
    std::vector<GLdouble> mCurveVertices2;
    std::vector<GLdouble> mCurveVertices3;
    std::vector<GLdouble> mCurveVertices4;
    std::vector<GLdouble> mColors;
    std::vector<GLdouble> displayControlPoints;
    std::vector<GLdouble> displayControlColors;
};

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow();
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();
    void setData(ContainerData data);
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
    std::vector<GLdouble> displayControlPoints;
    std::vector<GLdouble> displayControlColors;
    ContainerData mData;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
  
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_normAttr = 0;
    GLint m_projectionMatrixUniform = 0;
    GLint m_viewMatrixUniform = 0;
    GLint m_modelMatrixUniform = 0;
    GLint m_normalMatrixUniform = 0;
    GLint m_lightPosUniform = 0;

    QQuaternion rotationAngle;
    QPoint lastPos;
    float scaleFactor = 1.0;

    
};