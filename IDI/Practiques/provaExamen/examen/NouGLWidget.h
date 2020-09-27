#include "MyGLWidget.h"

class NouGLWidget : public MyGLWidget
{
 Q_OBJECT
	   
 public:
  NouGLWidget (QWidget *parent=NULL);
  ~NouGLWidget ();

 public slots:

 signals:

 protected:
  void paintGL ();
  void iniCamera ();
  void iniEscena ();
  void viewTransform ();
  void projectTransform ();
  void modelTransformPatricio ();
  void modelTransformPatricio2 ();
  
  // keyPressEvent - Es cridat quan es prem una tecla
  void keyPressEvent (QKeyEvent *event);
  
 private:
    glm::vec3 posPatricio;
    bool patricioCam;
    
    glm::mat4 pat2TG;
    
    void canviarCamera();
    float ultimAngleX, ultimAngleY;
};
