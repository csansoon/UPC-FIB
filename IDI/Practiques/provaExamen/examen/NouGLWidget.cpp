#include "NouGLWidget.h"

#include <iostream>

NouGLWidget::NouGLWidget(QWidget *parent) : MyGLWidget(parent) {
  grabKeyboard();
}

NouGLWidget::~NouGLWidget ()
{
}

void NouGLWidget::paintGL() {
  MyGLWidget::paintGL();
  
  // Activem el VAO per a pintar el segon Patricio
  glBindVertexArray (MyGLWidget::VAO_Pat);
  // pintem el Patricio
  modelTransformPatricio2();
  glDrawArrays(GL_TRIANGLES, 0, MyGLWidget::patModel.faces().size()*3);
}

void NouGLWidget::iniCamera ()
{
  //MyGLWidget::iniCamera();
  
  rav = 1.0;
  angleY = 0.0f;
  angleX = -(float)M_PI/6.0f;

  projectTransform ();
  viewTransform ();
}

void NouGLWidget::iniEscena ()
{
  MyGLWidget::iniEscena();

  centreEsc = glm::vec3 (4, 2, 4);
  radiEsc = 6;
  
  posPatricio = glm::vec3(4, 0, 6);
}

void NouGLWidget::modelTransformPatricio ()
{
  // Codi per a la TG necessàriaS
  glm::mat4 patTG = glm::mat4(1.0f);
  patTG = glm::translate(patTG, glm::vec3(2, 0, 1));
  patTG = glm::rotate(patTG, (float)M_PI/2, glm::vec3(0,1,0));
  patTG = glm::scale(patTG, glm::vec3(2 * MyGLWidget::escalaPat, 2 * MyGLWidget::escalaPat, 2 * MyGLWidget::escalaPat));
  patTG = glm::translate(patTG, -MyGLWidget::centreBasePat);
  
  glUniformMatrix4fv(MyGLWidget::transLoc, 1, GL_FALSE, &patTG[0][0]);
}

void NouGLWidget::modelTransformPatricio2 ()
{
  // Codi per a la TG necessària
  pat2TG = glm::mat4(1.0f);
  pat2TG = glm::translate(pat2TG, posPatricio);
  pat2TG = glm::rotate(pat2TG, (float)M_PI, glm::vec3(0,1,0));
  pat2TG = glm::scale(pat2TG, glm::vec3(3 * MyGLWidget::escalaPat, 3 * MyGLWidget::escalaPat, 3 * MyGLWidget::escalaPat));
  pat2TG = glm::translate(pat2TG, -MyGLWidget::centreBasePat);
  
  glUniformMatrix4fv(MyGLWidget::transLoc, 1, GL_FALSE, &pat2TG[0][0]);
}

void NouGLWidget::viewTransform() {
  //MyGLWidget::viewTransform();
  glm::vec3 posFocus;
  
  // Matriu de posició i orientació
  if (patricioCam)
  {
      View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
      View = glm::rotate(View, 0.0f, glm::vec3(1, 0, 0));
      View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
      View = glm::translate(View, -posPatricio);

      posFocus = glm::vec3(View * pat2TG * glm::vec4(0, 3.5, 0, 0.0));
      
      glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  else 
  {
      posFocus = glm::vec3(0, 0, 0);
      
      View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
      View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
      View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
      View = glm::translate(View, -centreEsc);

      glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
  
  glUniform3fv(posFocusLoc, 1, &posFocus[0]);
  
}

void NouGLWidget::projectTransform() {
  //MyGLWidget::projectTransform();
  
  float fov, zn, zf;
  glm::mat4 Proj;  // Matriu de projecció
  
  if (patricioCam)
  {
      fov = float(M_PI/2.0);
      zn = 0;
      zf = 13;
  }
  else
  {
      fov = float(M_PI/3.0);
      zn = radiEsc;
      zf = 3*radiEsc;
      
      if(rav < 1.0f){
          fov= atan(tan(0.5*fov)*radiEsc/rav);
          
    }
  }
  
  Proj = glm::perspective(fov, rav, zn, zf);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void NouGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: {
    if (posPatricio.z + 0.5 < 8) posPatricio.z += 0.5;
      break;
    }
    case Qt::Key_W: {
    if (posPatricio.z - 0.5 > 0) posPatricio.z -= 0.5;
      break;
    }
    case Qt::Key_A: {
    if (posPatricio.x - 0.5 > 0) posPatricio.x -= 0.5;

      break;
    }
    case Qt::Key_D: {
    if (posPatricio.x + 0.5 < 8) posPatricio.x += 0.5;
      break;
    }
    case Qt::Key_C: {
    canviarCamera();
      break;
    }
    default: {
      MyGLWidget::keyPressEvent(event);
      break;
    }
  }
  update();
}

void NouGLWidget::canviarCamera()
{
    patricioCam = !patricioCam;
    
    if (patricioCam)
    {
        ultimAngleX = angleX;
        ultimAngleY = angleY;
        
    }
    else
    {
        angleX = ultimAngleX;
        angleY = ultimAngleY;
    }
    
    iniCamera();
}
  
