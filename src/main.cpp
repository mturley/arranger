#include <QtGui/QApplication>
#include <QGraphicsPixmapItem>
#include <QListView>
#include <QScrollBar>

#include "view/mainwindow.h"
#include "model/score.h"
#include "model/staff.h"
#include "model/voice.h"
#include "model/phrase.h"
#include "lilygen.h"
#include "view/phrasewidget.h"
#include "view/phrasewidgetlistitem.h"
#include "view/phraselistmodel.h"
#include "view/phraselistdelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
