#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T01:29:44
#
#-------------------------------------------------

QT      += core gui

TARGET = arranger
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/lilytools.cpp \
    src/lilyhighlighter.cpp \
    src/lilygen.cpp \
    src/model/voice.cpp \
    src/model/staff.cpp \
    src/model/score.cpp \
    src/model/phrase.cpp \
    src/model/displayable.cpp \
    src/view/phrasewidgetlistitem.cpp \
    src/view/phrasewidget.cpp \
    src/view/phraselistmodel.cpp \
    src/view/phraselistdelegate.cpp \
    src/view/phraseeditor.cpp \
    src/view/mainwindow.cpp



HEADERS += \
    src/lilytools.h \
    src/lilyhighlighter.h \
    src/lilygen.h \
    src/model/voice.h \
    src/model/staff.h \
    src/model/score.h \
    src/model/phrase.h \
    src/model/displayable.h \
    src/view/phrasewidgetlistitem.h \
    src/view/phrasewidget.h \
    src/view/phraselistmodel.h \
    src/view/phraselistdelegate.h \
    src/view/phraseeditor.h \
    src/view/mainwindow.h



FORMS   += ui/mainwindow.ui
