#include <QtGui/QApplication>
#include <QGraphicsPixmapItem>
#include <QListView>
#include <QScrollBar>

#include "mainwindow.h"
#include "phrase.h"
#include "lilygen.h"
#include "phrasewidget.h"
#include "phrasewidgetlistitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Phrase* phrase1 = new Phrase("PhraseI","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4) d'2 ) e2( < f e g >4 c4 g8 a8 g4)");
    //Phrase* phrase2 = new Phrase("PhraseII","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4 d2 e2( f4 c4 g8 a8 g4)");
    //Phrase* phrase3 = new Phrase("PhraseIII","e8 e e e f g f e c' c c d c b a g");
    //Phrase* phrase4 = new Phrase("PhraseIV","f1~ f");

    phrase1->refresh();
    //phrase2->refresh();
    //phrase3->refresh();
    //phrase4->refresh();

    //PhraseWidget* someWidget = new PhraseWidget(phrase1);
    //QListWidgetItem* first = new QListWidgetItem();
    //first->setSizeHint(QSize(100,50));
    //w.ui->listWidget->addItem(first);
    //w.ui->listWidget->setItemWidget(first,someWidget);

    new PhraseWidgetListItem(phrase1,w.ui->listWidget);
    //new PhraseWidgetListItem(phrase2,w.ui->listWidget);
    //new PhraseWidgetListItem(phrase3,w.ui->listWidget);
    //new PhraseWidgetListItem(phrase4,w.ui->listWidget);
    //w.ui->listWidget->addItem(listItem);

    return a.exec();
}
