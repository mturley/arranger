#include <QtGui/QApplication>
#include <QGraphicsPixmapItem>
#include <QListView>

#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"
#include "phraseeditor.h"
#include "phraselistmodel.h"
#include "phrasedelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QListView view;
    PhraseListModel* model = new PhraseListModel();
    PhraseDelegate* delegate = new PhraseDelegate();

    view.setModel(model);
    view.setItemDelegate(delegate);

    Phrase* phrase1 = new Phrase("PhraseI","c1");
    Phrase* phrase2 = new Phrase("PhraseII","d1");
    Phrase* phrase3 = new Phrase("PhraseIII","e1");
    Phrase* phrase4 = new Phrase("PhraseIV","f1");

    model->append(phrase1);
    model->append(phrase2);
    model->append(phrase3);
    model->append(phrase4);

    phrase1->refresh();
    phrase2->refresh();
    phrase3->refresh();
    phrase4->refresh();

    view.show();

    /*
    Phrase phrase("PhraseIII","c4.( b4.)  e4 \n g8( a8 g8 a8 a4 a4)\n b4~ b8 b8( c8 g8\\( d'8\\) d8)");
    phrase.refresh();

    QGraphicsScene scene(0,0,600,300);
    w.ui->graphicsView->setScene(&scene);

    PhraseEditor* pe1 = new PhraseEditor(&phrase);

    w.ui->graphicsView->scene()->addItem(pe1);
    */

    return a.exec();
}
