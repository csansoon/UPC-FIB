
//#include <GL/glew.h>
#include "MyGLWidget.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#define GLM_FORCE_RADIANS

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
 
  
  scale1 = glm::vec3(0.5, 0.5, 1.0);
  translation1 = glm::vec3(0.5, 0.5, 0.0);
  rotation1 = 0;
  
  scale2 = glm::vec3(1.0, 1.0, 1.0);
  translation2 = glm::vec3(0.0, 0.0, 0.0);
  rotation2 = 0;
  
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::keyPressEvent (QKeyEvent *e) {
    makeCurrent();
    switch (e->key()) {
        case Qt::Key_S:
            scale2.y -= 0.05;
            scale2.x -= 0.01;
            break;
        case Qt::Key_D:
            scale2.y += 0.05;
            scale2.x += 0.01;
            break;
        
        case Qt::Key_Up:
            translation2.y += 0.05;
            break;
        case Qt::Key_Down:
            translation2.y -= 0.05;
            break;
        case Qt::Key_Left:
            translation2.x -= 0.05;
            break;
        case Qt::Key_Right:
            translation2.x += 0.05;
            break;
        
        default:
            e->ignore();
    }
    update();

}

void MyGLWidget::modelTransform1() {
    glm::mat4 TG (1.0);
    //rotation1 += (M_PI/4) * 0.25;
    TG = glm::translate (TG, translation1);
    TG = glm::rotate (TG, rotation1, glm::vec3(0.0,0.0,1.0));
    TG = glm::scale (TG, scale1);
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransform2() {
    glm::mat4 TG (1.0);
    rotation2 -= (M_PI/4) * 0.25;
    TG = glm::translate (TG, translation2);
    TG = glm::rotate (TG, rotation2, glm::vec3(0.0,0.0,1.0));
    TG = glm::scale (TG, scale2);
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
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

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  modelTransform1();
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  modelTransform2();
  glBindVertexArray(VAO3);
  
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ample = w;
  alt = h;
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices1[3];  // Tres vèrtexs amb X, Y i Z
  Vertices1[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices1[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices1[2] = glm::vec3(0.0, 1.0, 0.0);
  
  glm::vec3 Colors1[3];  // Tres colors amb R, G i B
  Colors1[0] = glm::vec3(1.0, 0.0, 0.0);
  Colors1[1] = glm::vec3(0.0, 1.0, 0.0);
  Colors1[2] = glm::vec3(0.0, 0.0, 1.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors1), Colors1, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  
  
  glm::vec3 Vertices2[3];  // Tres vèrtexs amb X, Y i Z
  Vertices2[0] = glm::vec3(1.0, 1.0, 0.0);
  Vertices2[1] = glm::vec3(-1.0, 1.0, 0.0);
  Vertices2[2] = glm::vec3(0.0, -1.0, 0.0);
  
  glm::vec3 Colors2[3];  // Tres colors amb R, G i B
  Colors2[0] = glm::vec3(1.0, 1.0, 0.0);
  Colors2[1] = glm::vec3(0.0, 1.0, 1.0);
  Colors2[2] = glm::vec3(1.0, 0.0, 1.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO3);
  glBindVertexArray(VAO3);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO3;
  glGenBuffers(1, &VBO3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO4;
  glGenBuffers(1, &VBO4);
  glBindBuffer(GL_ARRAY_BUFFER, VBO4);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors2), Colors2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  
  
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
  vertexLoc =   glGetAttribLocation (program->programId(), "vertex");
  colorLoc =    glGetAttribLocation (program->programId(), "color");
  transLoc =    glGetUniformLocation (program->programId(), "TG");
}
