#include <QtGui/QApplication>
#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"
#include "phraseeditor.h"
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase phrase("PhraseIII","c4.( b4.)  e4 \n g8( a8 g8 a8 a4 a4)\n b4~ b8 b8( c8 g8\\( d'8\\) d8)");
    phrase.refresh();

    QGraphicsScene scene(0,0,600,300);
    w.ui->graphicsView->setScene(&scene);

    PhraseEditor* pe1 = new PhraseEditor(&phrase);

    w.ui->graphicsView->scene()->addItem(pe1);

    return a.exec();
}
