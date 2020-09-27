#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  scale = 1.0f;
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

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  
  OBS = glm::vec3(0.0, 0.5, 1.5);
  VRP = glm::vec3(0.0, 0.0, 0.0);
  direction = glm::vec2(0.0, 0.0);

  homerScale = glm::vec3(1,1,1);
  homerTranslation = glm::vec3(0,0,0);
  homerRotation = 0;
  
  terraScale = glm::vec3(1,1,1);
  terraTranslation = glm::vec3(0,0,0);
  terraRotation = 0;
  
  escenaInicial();
  
  //Activar el z-buffer
  glEnable (GL_DEPTH_TEST);
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
  
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);
  
  // Esborrem el Z-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // Carreguem, transformem i pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransform (terraTranslation, terraScale, terraRotation);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  

  // Carreguem, transformem i pintem el Homer
  glBindVertexArray(VAO_Homer);
  modelTransform (homerTranslation, homerScale, homerRotation);
  glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);
  
  

  glBindVertexArray (0);
}

void MyGLWidget::escenaInicial() {
    
    fovIni = M_PI / 2.0f; //fov en radians
    fov = fovIni;
    ra = 1;
    znear = 0.4f;
    zfar = 3.0f;
    
    ini_camera();
}

void MyGLWidget::ini_camera () 
{
    projectTransform();
    viewTransform();
}

void MyGLWidget::modelTransform (glm::vec3 translation, glm::vec3 scale, float rotation) 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  
  transform = glm::translate(transform, translation);
  transform = glm::rotate(transform, rotation, glm::vec3(0, 1, 0));
  transform = glm::scale(transform, glm::vec3(scale));
  
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform () 
{
    glm::mat4 Proj;
    
    Proj = glm::perspective (fov,   ra,   znear,   zfar);
    
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
    glm::mat4 View;
    //                  (Cam Pos)             (look at this point)
    // glm::lookAt      (OBS,               VRP,                UP)
    View = glm::lookAt (OBS,                VRP,   glm::vec3(0,1,0));
    
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_R: { // Rotar el homer M_PI/4 radians en l'eix Y
      homerRotation += M_PI/4;
      paintGL();
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffers () 
{
  // Dades del terra
  // Dos VBOs, un amb posició i l'altre amb color
  glm::vec3 posicio[6] = {
	glm::vec3(-2, -1, -2),  //G
	glm::vec3(-2, -1, 2),   //B
	glm::vec3(2, -1, -2),   //Y
  
	glm::vec3(2, -1, -2),   //Y
	glm::vec3(-2, -1, 2),   //B
	glm::vec3(2, -1, 2)     //R
  }; 
  glm::vec3 color[6] = {
	glm::vec3(0,1,0),
	glm::vec3(0,0,1),
	glm::vec3(1,1,0),
	glm::vec3(1,1,0),
	glm::vec3(0,0,1),
	glm::vec3(1,0,0)
  };
  
  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  
  
  
  m.load("models/HomerProves.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  GLuint VBO_Homer[2];
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);


  glBindVertexArray (0);
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
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");
}

