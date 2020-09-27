TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h

SOURCES += ./Model/model.cpp main.cpp MyForm.cpp \
        MyGLWidget.cpp
