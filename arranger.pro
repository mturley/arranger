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
    src/phrasewidget.cpp \
    src/phrasewidgetlistitem.cpp \
    src/phraseeditor.cpp \
    src/lilyhighlighter.cpp \
    src/phraselistmodel.cpp \
    src/phraselistdelegate.cpp \
    src/score.cpp \
    src/staff.cpp


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
    src/phrasewidget.h \
    src/phrasewidgetlistitem.h \
    src/phraseeditor.h \
    src/lilyhighlighter.h \
    src/phraselistmodel.h \
    src/phraselistdelegate.h \
    src/projectmodel.h \
    src/iparentitem.h \
    src/ichilditem.h


FORMS   += ui/mainwindow.ui
