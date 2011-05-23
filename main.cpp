#include <QtGui/QApplication>
#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase p1("phrase1","c4");
    Phrase p2("phrase2","c4");
    Phrase p3("phrase3","c4");
    Phrase p4("phrase4","c4");
    p1.refresh();
    p2.refresh();
    p3.refresh();
    p4.refresh();

    return a.exec();
}
