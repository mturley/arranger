#include <QtGui/QApplication>
#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase p1("phrase1","c'8 d'8 c'8 e'8 f'2");
    Phrase p2("phrase2","c'4 d'4 e'4 f'4");
    Phrase p3("phrase3","cx'x4.( b'4.) e'8 e'4");
    Phrase p4("phrase4","c'4 c'2 c'4");

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
    QGraphicsPixmapItem* item1 = w.ui->graphicsView->scene()->addPixmap(*p1.getPreviewPixmap());
    QGraphicsPixmapItem* item2 = w.ui->graphicsView->scene()->addPixmap(*p2.getPreviewPixmap());
    QGraphicsPixmapItem* item3 = w.ui->graphicsView->scene()->addPixmap(*p3.getPreviewPixmap());
    QGraphicsPixmapItem* item4 = w.ui->graphicsView->scene()->addPixmap(*p4.getPreviewPixmap());
    item2->setPos(0,item1->y() + item1->pixmap().height());
    item3->setPos(0,item2->y() + item2->pixmap().height());
    item4->setPos(0,item3->y() + item3->pixmap().height());
    //w.ui->graphicsView->scene()->addPixmap(*p3.getPreviewPixmap());
    //w.ui->graphicsView->scene()->addPixmap(*p4.getPreviewPixmap());
    //w.ui->graphicsView->scene()->addRect(10,10,50,50);

    return a.exec();
}
