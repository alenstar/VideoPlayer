#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T14:40:05
#
#-------------------------------------------------

QT       += core gui multimedia opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        myglwidget.cpp \
        videowidgetsurface.cpp \
    ml/audiodecoder.cpp \
    ml/libavwrapper.cpp \
    ml/SDLMovieAudioFactory.cpp \
    ml/videoplayer.cpp \
    ml/videostate.cpp

HEADERS  += myglwidget.h \
        videowidgetsurface.h \
    ml/audiodecoder.hpp \
    ml/audiofactory.hpp \
    ml/SDLMovieAudioFactory.h \
    ml/videodefs.hpp \
    ml/videoplayer.hpp \
    ml/videostate.hpp

#avi.files += avi/*
#avi.path = $$OUT_PWD/debug
#INSTALLS += avi

LIBS += -lglut -lGLU -lSDL2 -lavformat -lavdevice -lavcodec -lavutil -lavfilter -lswscale
