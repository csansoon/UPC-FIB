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

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  iniEscena ();
  iniCamera ();
}

void MyGLWidget::iniEscena ()
{
  creaBuffersTerra();
  creaBuffersCub();
  creaBuffersPatricio();
  
  centreEsc = glm::vec3(10,3,10);
  radiEsc = distance(glm::vec3(0, 0, 0), glm::vec3(10, 3, 10));
  posPatricio = glm::vec3(0, 0, 0);
  rotacioPatricio = 0.0f;
}

void MyGLWidget::iniCamera ()
{
  primeraPersona = false;
  angleY = angleX = 0.0;
  obs = glm::vec3(0, 0, -radiEsc * 2);
  vrp = centreEsc;
  up = glm::vec3(0,1,0);
  ra = 1.0;
  fovIni = M_PI/3.0;
  fov = fovIni;
  distancia = distance(centreEsc + obs, centreEsc);
  zn = distancia - radiEsc;
  zf = distancia + radiEsc;
  
  fovPrimeraPersona = 60 * M_PI / 180;

  projectTransform ();
  viewTransform ();
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
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el Terra 
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // Activem el VAO per a pintar la Paret1
  glBindVertexArray (VAO_Cub);
  modelTransformParet1 ();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  
  // Activem el VAO per a pintar la Paret2
  glBindVertexArray (VAO_Cub);
  modelTransformParet2 ();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  
  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patricio);
  modelTransformPatricio ();
  glDrawArrays(GL_TRIANGLES, 0, patricio.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;

  ra = float(ample)/float(alt);
  
  if (ra < 1) fov = 2 * atan(tan(fovIni / 2) / ra);
  
  projectTransform ();
  glViewport(0, 0, w, h);
}

void MyGLWidget::modelTransformHomer ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  TG = glm::translate(TG, glm::vec3 (2, 1, 0.5));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  
  TG = glm::translate(TG, glm::vec3(10, 0, 10));
  TG = glm::scale(TG, glm::vec3(escalaPatricio) * 1.f);
  TG = glm::translate(TG, posPatricio/escalaPatricio);
  TG = glm::rotate(TG, rotacioPatricio, glm::vec3(0,1,0));
  TG = glm::translate(TG, -centreBasePatricio);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformParet1()  // Cal modificar aquesta funció...
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  
  TG = glm::translate(TG, glm::vec3(10, 0, 16));
  TG = glm::scale(TG, glm::vec3(0.6,6,8));
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformParet2()  // Cal modificar aquesta funció...
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  
  TG = glm::translate(TG, glm::vec3(10, 0, 4));
  TG = glm::scale(TG, glm::vec3(0.6,6,8));
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra ()
{
  glm::mat4 TG(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform () // Cal modificar aquesta funció...
{
  glm::mat4 Proj;  // Matriu de projecció
  
  if (primeraPersona)   Proj = glm::perspective(fovPrimeraPersona, ra, 0.1f, 30.f);
  else                  Proj = glm::perspective(fov, ra, zn, zf);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () // Cal modificar aquesta funció...
{
  glm::mat4 View;  // Matriu de posició i orientació

  //View = glm::lookAt(obs, vrp, up);
  if (primeraPersona)
  {
    glm::vec3 obsNew = glm::vec3(0.f, -0.5f, 0.f) + centreEsc + posPatricio;
    glm::vec3 vrpNew = obsNew + glm::vec3(sin(rotacioPatricio), 0.f, cos(rotacioPatricio));
    View = glm::lookAt(obsNew, vrpNew, glm::vec3(0,1,0));
  }
  else
  {
    View = glm::translate   (glm::mat4(1.0f), obs);
    View = glm::rotate      (View,  -angleY,   glm::vec3(1, 0, 0));
    View = glm::rotate      (View,  -angleX,    glm::vec3(0, 1, 0));
    View = glm::translate   (View,  -centreEsc);
  }

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)  // Cal modificar aquesta funció...
{
  makeCurrent();
  switch (event->key()) {
	case Qt::Key_Left: {
        glm::vec3 newPos = posPatricio + glm::vec3(-0.5f, 0.f, 0.f);
        if (newPos.x <= -10.f) break; //No sortir dels limits del terra
        else if (newPos.z <= -2.f || newPos.z >= 2.f) {
            if (newPos.x <= 0.3f && newPos.x >= -0.3f) break; //No travessar les parets.
        }
        posPatricio = newPos;
	  break;
	}
	case Qt::Key_Right: {
        glm::vec3 newPos = posPatricio + glm::vec3(0.5f, 0.f, 0.f);
        if (newPos.x >= 10.f) break; //No sortir dels limits del terra
        else if (newPos.z <= -2.f || newPos.z >= 2.f) {
            if (newPos.x <= 0.3f && newPos.x >= -0.3f) break; //No travessar les parets.
        }
        posPatricio = newPos;
	  break;
	}
    case Qt::Key_Up: {
        glm::vec3 newPos = posPatricio + glm::vec3(0.f, 0.f, -0.5f);
        if (newPos.z <= -10.f) break; //No sortir dels limits del terra
        else if (newPos.x <= 0.3f && newPos.x >= -0.3f) {
            if (newPos.z <= -2.f || newPos.z >= 2.f) break; //No travessar les parets.
        }
        posPatricio = newPos;
	  break;
	}
    case Qt::Key_Down: {
        glm::vec3 newPos = posPatricio + glm::vec3(0.f, 0.f, 0.5f);
        if (newPos.z >= 10.f) break; //No sortir dels limits del terra
        else if (newPos.x <= 0.3f && newPos.x >= -0.3f) {
            if (newPos.z <= -2.f || newPos.z >= 2.f) break; //No travessar les parets.
        }
        posPatricio = newPos;
	  break;
	}
	case Qt::Key_R: {
        rotacioPatricio += M_PI/2;
	  break;
	}
	case Qt::Key_I: {
        posPatricio = glm::vec3(0);
        rotacioPatricio = 0;
	  break;
	}
	case Qt::Key_C: {
        primeraPersona = !primeraPersona;
        projectTransform();
        viewTransform();
	  break;
	}
    default: event->ignore(); break;
  }

  if (primeraPersona) viewTransform();
  update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if (DoingInteractive == ROTATE)
  {
    angleX += (e->x() - xClick) * 0.03;
    angleY += (e->y() - yClick) * 0.03;
    
    //x_ant = e->x();
    //y_ant = e->y();

    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }
  escala = 2.0/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; 
  centreBase[1] = miny; 
  centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::creaBuffersCub ()
{
  // Dades del cub
  // Vèrtexs del cub
  glm::vec3 vertexs[8] = {
       /* 0*/ glm::vec3( -0.5, 0.0, -0.5),  /* 1*/ glm::vec3( 0.5, 0.0, -0.5),
       /* 2*/ glm::vec3( -0.5, 1.0, -0.5),  /* 3*/ glm::vec3( 0.5, 1.0, -0.5),
       /* 4*/ glm::vec3( -0.5, 0.0, 0.5),  /* 5*/ glm::vec3( 0.5, 0.0, 0.5),
       /* 6*/ glm::vec3( -0.5, 1.0, 0.5),  /* 7*/ glm::vec3( 0.5, 1.0, 0.5)
  };

  // VBO amb la posició dels vèrtexs
  glm::vec3 poscub[36] = {  // 12 triangles
       vertexs[0], vertexs[2], vertexs[1],
       vertexs[1], vertexs[2], vertexs[3],
       vertexs[5], vertexs[1], vertexs[7],
       vertexs[1], vertexs[3], vertexs[7],
       vertexs[2], vertexs[6], vertexs[3],
       vertexs[3], vertexs[6], vertexs[7],
       vertexs[0], vertexs[4], vertexs[6],
       vertexs[0], vertexs[6], vertexs[2],
       vertexs[0], vertexs[1], vertexs[4],
       vertexs[1], vertexs[5], vertexs[4],
       vertexs[4], vertexs[5], vertexs[6],
       vertexs[5], vertexs[7], vertexs[6]
  };
  
  glm::vec3 color(0, 0, 1.0);

  glm::vec3 colorcub[36] = {
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color
  };
  
  // Creació del Vertex Array Object del cub
  glGenVertexArrays(1, &VAO_Cub);
  glBindVertexArray(VAO_Cub);

  GLuint VBO_Cub[2];
  glGenBuffers(2, VBO_Cub);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(poscub), poscub, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorcub), colorcub, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersHomer ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  homer.load("./models/HomerProves.obj");
  
  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  // Creació dels buffers del model
  GLuint VBO_Homer[2];
  // Buffer de posicions
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*homer.faces().size()*3*3, homer.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de component difusa usada com a color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*homer.faces().size()*3*3, homer.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}


void MyGLWidget::creaBuffersPatricio ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  patricio.load("./models/Patricio.obj");
  
  // Creació del Vertex Array Object del Patricio
  glGenVertexArrays(1, &VAO_Patricio);
  glBindVertexArray(VAO_Patricio);

  // Creació dels buffers del model
  GLuint VBO_Patricio[2];
  // Buffer de posicions
  glGenBuffers(2, VBO_Patricio);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patricio.faces().size()*3*3, patricio.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de component difusa usada com a color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*patricio.faces().size()*3*3, patricio.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
  
  calculaCapsaModel(patricio, escalaPatricio, centreBasePatricio);
}


void MyGLWidget::creaBuffersTerra ()
{
  // Dades del terra
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[6] = {
	glm::vec3(0.0, 0.0, 20.0),
	glm::vec3(20.0, 0.0, 20.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(20.0, 0.0, 20.0),
	glm::vec3(20.0, 0.0, 0.0),
  }; 

  glm::vec3 color(0.0,0.6,0.0);

  // Fem que aquest material afecti a tots els vèrtexs per igual
  glm::vec3 colterra[6] = {
	color, color, color, color, color, color
  };

// Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colterra), colterra, GL_STATIC_DRAW);

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicShader.frag");
  vs.compileSourceFile("./shaders/basicShader.vert");
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

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");
}

