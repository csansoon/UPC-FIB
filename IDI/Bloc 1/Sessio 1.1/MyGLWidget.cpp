
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::paintGL ()
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

  //Esborrar pantalla:
  glClear (GL_COLOR_BUFFER_BIT);

  
  //Primer Viewport:
  glViewport (0, 0, ample/2, alt/2);
  //Activar Array VAO1:
  glBindVertexArray(VAO1);
  //Pintar l'Array;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
  //Activar Array VAO2:
  glBindVertexArray(VAO2);
  //Pintar l'Array;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
  
  
  //Segon Viewport:
  glViewport (ample/2, alt/2, ample/2, alt/2); 
  
  //Activar Array VAO1:
  glBindVertexArray(VAO1);
  //Pintar l'Array;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
  //Activar Array VAO2:
  glBindVertexArray(VAO2);
  //Pintar l'Array:
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
  
  
  //Desactivar el VAO:
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ample = w;
  alt = h;
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices[5];  // Cinc vèrtexs amb X, Y i Z (CASA)
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(0.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(-1.0, 0.0, 0.0);
  Vertices[3] = glm::vec3(0.0, 0.0, 0.0);
  Vertices[4] = glm::vec3(-0.5, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  
  
  glm::vec3 Vertices2[3];  // Tres vèrtexs amb X, Y i Z (TRIANGLE)
  Vertices2[0] = glm::vec3(0.0, 0.0, 0.0);
  Vertices2[1] = glm::vec3(0.5, 1.0, 0.0);
  Vertices2[2] = glm::vec3(1.0, 0.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc2);

  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  vertexLoc2 = glGetAttribLocation (program->programId(), "vertex");
}
