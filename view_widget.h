#ifndef VIEW_WIDGET_H
#define VIEW_WIDGET_H

#include <QBasicTimer>
#include <QColorDialog>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector2D>
#include <QTimer>

#include "geometryengine.h"

class GeometryEngine;

class view_widget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~view_widget();
    GeometryEngine *geometries = nullptr;
    QColor *color = new QColor(255, 249, 0, 255);
    QColor *color_back = new QColor(152, 255, 152, 255);
    QColor *color_ver = new QColor(17, 242, 0, 255);
    int check_projection = 0;
    int line_width = 1;
    int line_type = 0;
    void setTimer();
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QString path_convert;

protected:
    void initializeGL() override;
    void initShaders();
    //  void initTextures();
    void initColors();
    void initColorsVer();
    void timerEvent(QTimerEvent *e) override;

private:
    QBasicTimer timer;
    unsigned counter = 0;

    QOpenGLShaderProgram program;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QQuaternion rotation;
};

#endif  // VIEW_WIDGET_H
