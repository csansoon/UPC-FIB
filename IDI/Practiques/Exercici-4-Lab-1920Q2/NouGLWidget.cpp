#include "NouGLWidget.h"

#include <iostream>

NouGLWidget::NouGLWidget(QWidget *parent) : MyGLWidget(parent) {
  grabKeyboard();
}

NouGLWidget::~NouGLWidget ()
{
}

void NouGLWidget::initializeGL() {
  MyGLWidget::initializeGL();
  carregaShaders();
  
  
  posFocusLlum = glm::vec3(3.0, 3.8, 0.5);
  colFocusLlum = glm::vec3(1.0, 1.0, 1.0);
  
  posFocusEspasa = glm::vec3(1.85, 20.0, 7.3);
  colFocusEspasa = glm::vec3(0.5, 1.0, 0.0);
  
  setPosFocus(posFocusLlum.x, posFocusLlum.y, posFocusLlum.z);
  LlumAEspasa = false;
  actualitzaLlum();
}

void NouGLWidget::modelTransformLego ()
{
  MyGLWidget::modelTransformLego();
  actualitzaLlum();
}

void NouGLWidget::viewTransform() {
  MyGLWidget::viewTransform();
}

void NouGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      setPosFocus(posFocusLlum.x - 0.2, posFocusLlum.y, posFocusLlum.z);
        break;
    }
  case Qt::Key_D: {
      setPosFocus(posFocusLlum.x + 0.2, posFocusLlum.y, posFocusLlum.z);
      break;
	}
  case Qt::Key_F: {
      LlumAEspasa = !LlumAEspasa;
      actualitzaLlum();
      break;
	}
  default: {
    MyGLWidget::keyPressEvent(event);
    break;
	}
  }
  update();
}

void NouGLWidget::setPosFocus(float x, float y, float z)
{
    if (x < 0) x = 0;
    if (x > 6) x = 6;
    
    posFocusLlum.x = x;
    actualitzaLlum();
    
    int sliderPos = x * 10;
    emit actualitzaSlider(sliderPos);
}

void NouGLWidget::actualitzaLlum()
{
    if (LlumAEspasa)
    {
        glm::vec3 posFocusEspasaModel = glm::vec3(MyGLWidget::View * MyGLWidget::legoTG * glm::vec4(posFocusEspasa, 1.0));
        glUniform3fv(posFocusLoc, 1, &posFocusEspasaModel[0]);
        glUniform3fv(colFocusLoc, 1, &colFocusEspasa[0]);
        
        glUniform1i(llumEspasaLoc, 1);
    }
    else
    {
        glm::vec3 posFocusLlumEscena = glm::vec3(MyGLWidget::View * glm::vec4(posFocusLlum, 1.0));
        glUniform3fv(posFocusLoc, 1, &posFocusLlumEscena[0]);
        glUniform3fv(colFocusLoc, 1, &colFocusLlum[0]);
        
        glUniform1i(llumEspasaLoc, 0);
    }
    
}
  
void NouGLWidget::carregaShaders()
{
    //Obtenir identificarods:
    posFocusLoc = glGetUniformLocation(program->programId(), "posFocus");
    colFocusLoc = glGetUniformLocation(program->programId(), "colFocus");
    llumEspasaLoc = glGetUniformLocation(program->programId(), "llumEspasa");
}

void NouGLWidget::movePosFocus(int x)
{
    makeCurrent();
    setPosFocus((float)x / 10, 0, 0);
    update();
}
