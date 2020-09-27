#include "MyGLWidget.h"

class NouGLWidget : public MyGLWidget
{
 Q_OBJECT
 public slots:
     void movePosFocus(int);
     
     
 signals:
    void actualitzaSlider(int);
     
    
 public:
  NouGLWidget (QWidget *parent=NULL);
  ~NouGLWidget ();

 public slots:

 signals:

 protected:
  virtual void initializeGL ();
  virtual void viewTransform ();
  virtual void modelTransformLego ();
  
  // keyPressEvent - Es cridat quan es prem una tecla
  virtual void keyPressEvent (QKeyEvent *event);
  
 private:
     void carregaShaders();
     void actualitzaLlum();
     
     GLuint posFocusLoc, colFocusLoc, llumEspasaLoc;
     glm::vec3 posFocusEspasa, posFocusLlum;
     glm::vec3 colFocusEspasa, colFocusLlum;
     
     glm::vec3 posLlumEspasa;
     bool LlumAEspasa;
     
     void setPosFocus(float x, float y, float z);
};
