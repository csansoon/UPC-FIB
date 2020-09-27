#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

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

  private:
    
    void creaBuffers ();
    void carregaShaders ();
    
    void escenaInicial();
    
    void ini_camera();
    
    void modelTransform (glm::vec3 translation, glm::vec3 scale, float rotation);
    void projectTransform ();
    void viewTransform ();

    void calculaCentreEscena();
    void calculaRadiEscena();
    void calculaCapsaEscena();
    void calculaModel(Model& m);

    // attribute locations
    GLuint vertexLoc, colorLoc;

    // uniform locations
    GLuint transLoc;
    GLuint projLoc;
    GLuint viewLoc;

    // VAO i VBO names
    GLuint VAO_Terra;
    GLuint VAO_Homer;

    // Program
    QOpenGLShaderProgram *program;

    // Viewport
    GLint ample, alt;

    // Internal vars
    bool axonometric;
    float scale;
    glm::vec3 centre_escena;
    float radi_escena;
    glm::vec3 minimEscena, maximEscena;
    
    float mRotation; glm::vec3 mScale, mTranslation;
    float terraRotation; glm::vec3 terraScale, terraTranslation;
    
//     glm::vec3 maxim, minim;
    
    glm::vec3 pos;
    float fovIni, fov, ra, znear, zfar;
    glm::vec3 OBS, VRP, UP;
    
    //  Models
    Model m;
    glm::vec3 minimModel, maximModel;
};
