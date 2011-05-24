#include <QtGui/QApplication>
#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase p1("phrase1","c'8 d'8 c'8 e'8 f'2");
    Phrase p2("phrase2","c'4 d'4 e'4 f'4");
    Phrase p3("phrase3","c'4.( b'4.) e'8 e'4");
    Phrase p4("phrase4","c'4 c'2 c'4");
    p1.refresh();
    p2.refresh();
    p3.refresh();
    p4.refresh();

    return a.exec();
}
