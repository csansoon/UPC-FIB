#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    virtual ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void modelTransformTerra ();
    virtual void modelTransformPatricio ();

    // Program
    QOpenGLShaderProgram *program;
    
    // VAO names
    GLuint VAO_Pat, VAO_Terra;

    // model
    Model patModel;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBasePat;
    float escalaPat;

    // uniform locations
    GLuint transLoc, projLoc, viewLoc, posFocusLoc;

    // escena
    glm::vec3 centreEsc;
    float radiEsc, rav;
    float angleX, angleY;

    // matrius
    glm::mat4 View;

  private:

    void creaBuffersModel(Model &model, const char *fileName, GLuint *VAO, float &escala, glm::vec3 &centreBase);
    void creaBuffersPatricio();
    void creaBuffersTerra ();
    void carregaShaders ();
    void calculaCapsaModel (Model &m, float &escala, glm::vec3 &centreBase);


    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    GLint ample, alt;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
};

