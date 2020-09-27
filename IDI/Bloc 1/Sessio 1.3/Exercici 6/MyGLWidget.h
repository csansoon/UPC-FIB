#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include <QKeyEvent>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  
    
    virtual void keyPressEvent (QKeyEvent *e);
    virtual void modelTransform1();
    virtual void modelTransform2();

  private:
    void creaBuffers ();
    void carregaShaders ();
    
    // attribute locations
    GLuint vertexLoc;
    GLuint colorLoc;
    GLuint varLoc;
    GLuint transLoc;
    
    float scl;
    float rotation1, rotation2;
    glm::vec3 scale1, scale2;
    glm::vec3 translation1, translation2;
    
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
    GLuint VAO3;
    GLint ample, alt;
};
