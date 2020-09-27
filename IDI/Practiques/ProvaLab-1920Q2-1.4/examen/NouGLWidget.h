#include "MyGLWidget.h"

class NouGLWidget : public MyGLWidget
{
 Q_OBJECT
	   
 public:
  NouGLWidget (QWidget *parent=NULL);
  ~NouGLWidget ();

 public slots:
    void setIntensitat(int);
    void setCamera();
        
 signals:
    void actualitzaSlider(int);

 protected:
  void paintGL ();
  void resizeGL (int w, int h);
  void iniCamera ();
  void iniEscena ();
  void viewTransform ();
  void projectTransform ();
  void modelTransformLego ();
  void modelTransformCub ();
  
  // keyPressEvent - Es cridat quan es prem una tecla
  void keyPressEvent (QKeyEvent *event);
  
 private:
  void setIntensitatFocus(float);
  void canviaCamera();
  bool primeraPersona;
     
  glm::vec3 legoPos, colFocus;
  bool legoVisible;
};
