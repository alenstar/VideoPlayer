#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T14:40:05
#
#-------------------------------------------------

QT       += core gui multimedia opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer
TEMPLATE = app

CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
    DEFINES += DEBUG
    #QMAKE_CXXFLAGS += -O3
}
else{
    CONFIG -= debug release
    CONFIG += release
    DEFINES += QT_NO_DEBUG_OUTPUT
    QMAKE_CXXFLAGS += -O3
}

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        myglwidget.cpp \
    ml/audiodecoder.cpp \
    ml/libavwrapper.cpp \
    ml/SDLMovieAudioFactory.cpp \
    ml/videoplayer.cpp \
    ml/videostate.cpp \
    streams/src/Buffer.cpp \
    streams/src/FileStream.cpp \
    streams/src/IOStream.cpp \
    streams/src/MemoryStream.cpp \
    streams/src/Stream.cpp \
    texture.cpp \
    Matrices.cpp \
    shader.cpp

HEADERS  += myglwidget.h \
    ml/audiodecoder.hpp \
    ml/audiofactory.hpp \
    ml/SDLMovieAudioFactory.h \
    ml/videodefs.hpp \
    ml/videoplayer.hpp \
    ml/videostate.hpp \
    texture.h \
    Matrices.h \
    Vectors.h \
    shader.h


INCLUDEPATH += streams/include
#avi.files += avi/*
#avi.path = $$OUT_PWD/debug
#INSTALLS += avi

LIBS += -pthread -lm -lglut -lGL -lGLU -lSDL2 -lavformat -lavdevice -lavcodec -lavutil -lavfilter -lswscale -lavresample
