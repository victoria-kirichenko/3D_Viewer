#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <iostream>
using namespace std;

GeometryEngine::GeometryEngine() : indexBuf(QOpenGLBuffer::IndexBuffer) {
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
  initCubeGeometry();
}

GeometryEngine::~GeometryEngine() {
  arrayBuf.destroy();
  indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry() {
  for (int i = 0; i < file.count_of_vertexes; ++i) {
    VertexData tmp_vert = {QVector3D(file.matrix_3d.matrix[i][0],
                                     file.matrix_3d.matrix[i][1],
                                     file.matrix_3d.matrix[i][2])};
    vertices.push_back(tmp_vert);
  }

  for (int i = 0; i < file.count_of_facets; i++) {
    for (int j = 0; j < file.polygons[i].numbers_of_vertexes_in_facets - 1;
         j++) {
      indices.push_back(file.polygons[i].vertexes[j] - 1);
      indices.push_back(file.polygons[i].vertexes[j + 1] - 1);
    }
    indices.push_back(file.polygons[i].vertexes[0] - 1);
    indices.push_back(
        file.polygons[i]
            .vertexes[file.polygons[i].numbers_of_vertexes_in_facets - 1] -
        1);
  }
  arrayBuf.bind();
  arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));
  indexBuf.bind();
  indexBuf.allocate(indices.data(), indices.size() * sizeof(GLuint));
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program) {
  // Tell OpenGL which VBOs to use
  indexBuf.bind();
  if (arrayBuf.isCreated()) {
    arrayBuf.destroy();
    arrayBuf.create();
    arrayBuf.bind();
    QVector<VertexData> vertices;
    for (int i = 0; i < file.count_of_vertexes; ++i) {
      VertexData tmp_vert = {QVector3D(file.matrix_3d.matrix[i][0],
                                       file.matrix_3d.matrix[i][1],
                                       file.matrix_3d.matrix[i][2])};
      vertices.push_back(tmp_vert);
    }
    arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));
  }
  arrayBuf.bind();

  //    // Offset for position
  quintptr offset = 0;

  //    // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  //    // Offset for texture coordinate
  offset += sizeof(QVector3D);

  //    // Tell OpenGL programmable pipeline how to locate vertex texture
  //    coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                              sizeof(VertexData));

  //    // Draw cube geometry using indices from VBO 1
  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void GeometryEngine::drawDots(QOpenGLShaderProgram *program) {
  if (dot_type == 0) return;
  if (dot_type == 1) {
    glDisable(GL_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SIZE);
  }
  glPointSize(size_vert);
  indexBuf.bind();
  if (arrayBuf.isCreated()) {
    arrayBuf.destroy();
    arrayBuf.create();
    arrayBuf.bind();
    QVector<VertexData> vertices;
    for (int i = 0; i < file.count_of_vertexes; ++i) {
      VertexData tmp_vert = {QVector3D(file.matrix_3d.matrix[i][0],
                                       file.matrix_3d.matrix[i][1],
                                       file.matrix_3d.matrix[i][2])};
      vertices.push_back(tmp_vert);
    }
    arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));
  }
  arrayBuf.bind();
  // Offset for position
  quintptr offset = 0;
  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));
  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate
  // data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2,
                              sizeof(VertexData));
  glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, nullptr);
}
