#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T01:29:44
#
#-------------------------------------------------

QT      += core gui

TARGET = arranger
TEMPLATE = app


SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/content.cpp \
    src/phrase.cpp \
    src/voice.cpp \
    src/lilygen.cpp \
    src/phraseeditor.cpp \
    src/phrasedelegate.cpp \
    src/phraselistmodel.cpp


HEADERS += \
    src/mainwindow.h \
    src/icontent.h \
    src/idisplayable.h \
    src/content.h \
    src/phrase.h \
    src/voice.h \
    src/staff.h \
    src/score.h \
    src/lilygen.h \
    src/phraseeditor.h \
    src/phrasedelegate.h \
    src/phraselistmodel.h


FORMS   += ui/mainwindow.ui
