#include "NouGLWidget.h"

#include <iostream>

NouGLWidget::NouGLWidget(QWidget *parent) : MyGLWidget(parent) {
  grabKeyboard();
}

NouGLWidget::~NouGLWidget ()
{
}

void NouGLWidget::paintGL() {
  //MyGLWidget::paintGL();
    
    
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

  //--------------------------------------------------------
  // Activem el VAO per pintar el terra
  glBindVertexArray (VAO_Terra);  
  // pintem terra
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 6);

  //--------------------------------------------------------
  // Activem el VAO per pintar el cub
  glBindVertexArray (VAO_Cub);
  // pintem cub
  modelTransformCub ();
  glDrawArrays(GL_TRIANGLES, 0, 36);

  //--------------------------------------------------------
  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Lego);
  // pintem el Patricio
  modelTransformLego();
  if (legoVisible) glDrawArrays(GL_TRIANGLES, 0, legoModel.faces().size()*3);

  //--------------------------------------------------------
  glBindVertexArray(0);
}

void NouGLWidget::resizeGL(int w, int h) {
  rav = float(w) / float(h);
  MyGLWidget::resizeGL(w, h);
}

void NouGLWidget::iniCamera ()
{
  //MyGLWidget::iniCamera();
    primeraPersona = false;
    
  rav = 1.0;
  angleY = 0.0;
  angleX = M_PI/6.0;

  projectTransform ();
  viewTransform ();
}

void NouGLWidget::iniEscena ()
{
  MyGLWidget::iniEscena();
  
  centreEsc = glm::vec3 (4, 1.5, 3);
  radiEsc = 5;
  
  glm::vec3 posFocus(8, 2.5, 6);
  colFocus = glm::vec3(1, 1, 1);
  glUniform3fv(posFocusLoc, 1, &posFocus[0]);
  
  setIntensitatFocus(1.f);
  glUniform3fv(colFocusLoc, 1, &colFocus[0]);
  
  legoPos = glm::vec3(4, 0, 5);
  legoVisible = true;
}

void NouGLWidget::modelTransformLego ()
{
  // Codi per a la TG necessària
  glm::mat4 legoTG = glm::mat4(1.0f);
  
  legoTG = glm::translate(legoTG, legoPos);
  legoTG = glm::rotate(legoTG, (float)M_PI, glm::vec3(0,1,0));
  legoTG = glm::scale(legoTG, glm::vec3(2 * escalaLego, 2 * escalaLego, 2 * escalaLego));
  
  legoTG = glm::translate(legoTG, -centreBaseLego);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &legoTG[0][0]);
}

void NouGLWidget::modelTransformCub ()
{
  glm::mat4 cubTG(1.f);
  
  cubTG = glm::translate(cubTG, glm::vec3(4, 0, 0.5));
  cubTG = glm::scale(cubTG, glm::vec3(6, 3, 0.5));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &cubTG[0][0]);
}

void NouGLWidget::viewTransform() {
  //MyGLWidget::viewTransform();
    
    if (primeraPersona)
    {
        glm::vec3 obs = glm::vec3(4, 2.5, 5);
        glm::vec3 vrp = obs + glm::vec3(0, 0, 10);
        View = glm::lookAt(obs, vrp, glm::vec3(0,1,0));
    }
    
    else
    {
        // Matriu de posició i orientació
        View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
        View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
        View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
        View = glm::translate(View, -centreEsc);
    }

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void NouGLWidget::projectTransform() {
  //MyGLWidget::projectTransform();
    
  float fov, zn, zf;
  glm::mat4 Proj;  // Matriu de projecció
  
  fov = float(M_PI/3.0);
  zn = radiEsc;
  zf = 3*radiEsc;
  
  if (rav < 1.0f) fov = atan(tan(0.5*fov)*radiEsc/rav);
    
  if (primeraPersona)   Proj = glm::perspective(float(M_PI/3.0), rav, 0.f, 7.f);
  else                  Proj = glm::perspective(fov, rav, zn, zf);

  
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void NouGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_W: {
        legoPos += glm::vec3(0, 0, 0.5);
        legoVisible = legoPos.z <= 6;
        
      break;
    }
    case Qt::Key_S: {
        if (legoPos.z - 0.5 >= 1.5) legoPos += glm::vec3(0, 0, -0.5);
        legoVisible = legoPos.z <= 6;
      break;
    }
    case Qt::Key_C: {
        canviaCamera();
      break;
    }
    case Qt::Key_O: {
        setIntensitatFocus(colFocus.x + 0.1);
      break;
    }
    case Qt::Key_L: {
        setIntensitatFocus(colFocus.x - 0.1);
      break;
    }
    default: {
      MyGLWidget::keyPressEvent(event);
      break;
    }
  }
  update();
}

void NouGLWidget::setIntensitatFocus(float intensitat)
{
    if (intensitat >= 0.f and intensitat <= 1.f) colFocus = glm::vec3(intensitat);
    glUniform3fv(colFocusLoc, 1, &colFocus[0]);
    
    emit actualitzaSlider(int(intensitat * 10));
}

void NouGLWidget::canviaCamera()
{
    primeraPersona = !primeraPersona;
    viewTransform();
    projectTransform();
}
  
  
void NouGLWidget::setIntensitat(int intensitat)
{
    makeCurrent();
    setIntensitatFocus(float(intensitat) / 10);
    update();
}
void NouGLWidget::setCamera()
{
    makeCurrent();
    canviaCamera();
    update();
}
