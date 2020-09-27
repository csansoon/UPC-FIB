#QMAKE_CXX = g++-9
#QMAKE_CXXFLAGS = -std=c++11

TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h NouGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        MyGLWidget.cpp NouGLWidget.cpp ./Model/model.cpp

