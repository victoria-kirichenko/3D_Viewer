#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

extern "C" {
#include "back.h"
}

struct VertexData {
  QVector3D position;
};

class GeometryEngine : protected QOpenGLFunctions {
 public:
  GeometryEngine();
  virtual ~GeometryEngine();
  void initCubeGeometry();
  void drawCubeGeometry(QOpenGLShaderProgram *program);
  void drawDots(QOpenGLShaderProgram *program);
  struct data file = {0, 0, {0, 0, 0}, 0};
  QVector<GLuint> indices;
  QVector<VertexData> vertices;
  int dot_type = 0;
  int size_vert = 5;

 private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
};

#endif  // GEOMETRYENGINE_H
