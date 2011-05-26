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

    Phrase p1("Phrase I","c'8 d'8 c'8 e'8 f'2");
    Phrase p2("Phrase II","c'4 d'4 e'4 f'4");
    Phrase p3("Phrase III","cx'x4.( b'4.) e'8 e'4");
    Phrase p4("Phrase IV","c'4 c'2 c'4");

    p3.refresh();
    p1.refresh();
    p2.refresh();

    p4.refresh();
    p4.refresh();
    p4.refresh();
    p4.refresh();

    sleep(2);

    p3.setContent("c'4.( b'4.) e'8 e'4");

    p1.refresh();
    p3.refresh();
    p3.refresh();

    sleep(2);

    QGraphicsScene scene(0,0,300,300);
    w.ui->graphicsView->setScene(&scene);

    PhraseEditor* pe1 = new PhraseEditor(&p3);

    w.ui->graphicsView->scene()->addItem(pe1);

    return a.exec();
}
