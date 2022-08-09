#include "view_widget.h"

#include <string.h>

#include <QFileDialog>
#include <QFutureWatcher>
#include <QMouseEvent>
#include <QtConcurrent>
#include <cmath>

QString path;
QString path1;
char *screen_command_line;
char *screen_command_line2;
QString q_screen_command_line;

view_widget::~view_widget() {
  makeCurrent();
  delete texture;
  delete geometries;
  doneCurrent();
}

void view_widget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  initShaders();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  geometries = new GeometryEngine;
}

void view_widget::initShaders() {
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
    close();

  // Compile fragment shader
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/fshader.glsl"))
    close();

  // Link shader pipeline
  if (!program.link()) close();

  // Bind shader pipeline for use
  if (!program.bind()) close();
}

void view_widget::initColors() {
  glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(),
               0);

  int vertexLocation = program.attributeLocation("vertex");
  int colorLocation = program.uniformLocation("color");

  program.enableAttributeArray(vertexLocation);
  program.setUniformValue(colorLocation, *color);
  program.disableAttributeArray(vertexLocation);
}

void view_widget::initColorsVer() {
  glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(),
               0);

  int vertexLocation = program.attributeLocation("vertex");
  int colorLocation = program.uniformLocation("color");

  program.enableAttributeArray(vertexLocation);
  program.setUniformValue(colorLocation, *color_ver);
  program.disableAttributeArray(vertexLocation);
}

void view_widget::resizeGL(int w, int h) {
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;

  projection.setToIdentity();
  if (check_projection == 1) {
    QRectF orthoRectangle;
    orthoRectangle.setHeight(h);
    orthoRectangle.setWidth(w);
    projection.ortho(-10.0, 10.0, -10.0, 10.0, -100, 100);
  } else {
    projection.perspective(fov, aspect, zNear, zFar);
  }
}

void view_widget::paintGL() {
  glLineWidth(line_width);
  initColors();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 matrix;
  matrix.translate(0.0, 0.0, -5.0);
  matrix.rotate(rotation);

  program.setUniformValue("mvp_matrix", projection * matrix);

  if (line_type) {
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 58360);
    geometries->drawCubeGeometry(&program);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
  } else {
    geometries->drawCubeGeometry(&program);
  }
  initColorsVer();
  geometries->drawDots(&program);
}

void view_widget::setTimer() {
  QString full_path = QCoreApplication::applicationDirPath();
  full_path += "/path_convert.txt";
  QFile file(full_path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    path_convert = file.readLine();
    path_convert.resize(path_convert.size() - 1);
  }

  QFileDialog file_dialog_photo(this);
  path.clear();
  path1.clear();
  path = file_dialog_photo.getSaveFileName(this, tr("Save a gif"), "", "");
  counter = 50;
  q_screen_command_line = "mkdir " + path;
  QByteArray temp = q_screen_command_line.toLocal8Bit();
  screen_command_line = temp.data();
  system(screen_command_line);
  screen_command_line2 = strcat(screen_command_line, "/screenshorts");
  system(screen_command_line2);
  path1 += path + "/screenshorts/";
  timer.start(100, this);
}

void view_widget::timerEvent(QTimerEvent *) {
  QString strCount = QString::number(counter);
  grabFramebuffer().save(path1 + strCount + ".jpg", NULL, 100);
  counter--;
  if (counter < 1) {
    QString q_command_line = path_convert +
                             " -delay 10 -loop 0 -alpha on -layers optimize "
                             "-dispose previous $(ls -1 " +
                             path1 + "*.jpg | sort -V) " + path + ".gif";

    QByteArray temp = q_command_line.toLocal8Bit();
    char *command_line = temp.data();
    system(command_line);
    timer.stop();
    q_command_line.clear();
  }
}
