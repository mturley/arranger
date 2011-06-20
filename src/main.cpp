#include <QtGui/QApplication>
#include <QGraphicsPixmapItem>
#include <QListView>
#include <QScrollBar>

#include "mainwindow.h"
#include "score.h"
#include "staff.h"
#include "voice.h"
#include "phrase.h"
#include "lilygen.h"
#include "phrasewidget.h"
#include "phrasewidgetlistitem.h"
#include "phraselistmodel.h"
#include "phraselistdelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
