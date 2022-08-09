QT       += core gui widgets opengl openglwidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    afinne.c \
    back.c \
    geometryengine.cpp \
    main.cpp \
    mainwindow.cpp \
    view_widget.cpp

HEADERS += \
    back.h \
    geometryengine.h \
    mainwindow.h \
    view_widget.h \

FORMS += \
    mainwindow.ui

RESOURCES += \
    shaders.qrc \

DISTFILES += \
    fshader.glsl \
    vshader.glsl

macx:ICON = logo.icns
