#include <QtGui/QApplication>
#include <QGraphicsPixmapItem>
#include <QListView>

#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"
#include "phrasewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase* phrase1 = new Phrase("PhraseI","c1");
    Phrase* phrase2 = new Phrase("PhraseII","d1");
    Phrase* phrase3 = new Phrase("PhraseIII","e1");
    Phrase* phrase4 = new Phrase("PhraseIV","f1");

    phrase1->refresh();
    phrase2->refresh();
    phrase3->refresh();
    phrase4->refresh();

    PhraseWidget* someWidget = new PhraseWidget(phrase1);
    QListWidgetItem* first = new QListWidgetItem();
    first->setSizeHint(QSize(100,50));
    w.ui->listWidget->addItem(first);
    w.ui->listWidget->setItemWidget(first,someWidget);

    return a.exec();
}
