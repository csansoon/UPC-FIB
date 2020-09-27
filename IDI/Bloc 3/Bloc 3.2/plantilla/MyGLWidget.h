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

public slots:
  void activa_llum(const bool & checkBox);
  //void activa_SCO(const bool & checkBox);
  void next_model();
  void previous_model();
  
  
signals:
    
    void actualitza_llum(const bool &);
    void actualitza_SCO(const bool &);
    void actualitza_nom_model(const QString &);
  
  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void createBuffersPatricio (std::string mod);
    void createBuffersTerraIParet ();
    void carregaShaders ();
    void iniEscena ();
    void iniCamera ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformPatricio ();
    void calculaCapsaModel ();
    
    void setIluminacio(bool);
    void setSCO(bool);
    void setModel(int);

    // VAO names
    GLuint VAO_Patr;
    GLuint VAO_Terra;
    // Program
    QOpenGLShaderProgram *program;
    // Viewport
    GLint ample, alt;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;
    GLuint ilumLoc, scoLoc, posFocusLoc, colFocusLoc;

    // model
    Model patr;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centrePatr;
    float escala;
    // radi de l'escena
    float radiEsc;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleX, angleY;
    bool perspectiva;
    bool iluminacio, SCO;
    glm::vec3 posFocus, colFocus;
    
    std::vector<std::string> models;
    int modelIndex;
};

