#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QScrollBar>

#include "phraselistdelegate.h"
#include "phraselistmodel.h"
#include "phrasewidgetlistitem.h"
#include "phrasewidget.h"
#include "../model/score.h"
#include "../model/staff.h"
#include "../model/voice.h"
#include "../model/phrase.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    //ui->listView->setResizeMode(QListView::Adjust);
    //ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    //PhraseListDelegate* delegate = new PhraseListDelegate();
    //PhraseListModel* model       = new PhraseListModel();

    //ui->listView->setModel(model);
    //ui->listView->setItemDelegate(delegate);

    Phrase* phraseA = new Phrase("PhraseAAALongNameTotally","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
    Phrase* phraseB = new Phrase("PhraseB","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4");
    Phrase* phraseC = new Phrase("PhraseC","e8 e e e f g f e c' c c d c b a g");
    Phrase* phraseD = new Phrase("PhraseD","f1~ f");
    Phrase* phraseE = new Phrase("PhraseE","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
    Phrase* phraseF = new Phrase("PhraseF","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4");
    Phrase* phraseG = new Phrase("PhraseG","e8 e e e f g f e c' c c d c b a g");
    Phrase* phraseH = new Phrase("PhraseH","f1~ f");

    phraseA->refresh();
    phraseB->refresh();
    phraseC->refresh();
    phraseD->refresh();
    phraseE->refresh();
    phraseF->refresh();
    phraseG->refresh();
    phraseH->refresh();

    //model->append(phraseA);
    //model->append(phraseB);
    //model->append(phraseC);
    //model->append(phraseD);
    //model->append(phraseE);
    //model->append(phraseF);
    //model->append(phraseG);
    //model->append(phraseH);

    // test tree models

    Score* scoreA = new Score("ScoreA");
    Score* scoreB = new Score("ScoreB");
    Score* scoreC = new Score("ScoreC");

    Staff* staffA = new Staff("StaffA");
    Staff* staffB = new Staff("StaffB");
    Staff* staffC = new Staff("StaffC");
    Staff* staffD = new Staff("StaffD");
    Staff* staffE = new Staff("StaffE");
    Staff* staffF = new Staff("StaffF");

    Voice* voiceA = new Voice("VoiceA");
    Voice* voiceB = new Voice("VoiceB");
    Voice* voiceC = new Voice("VoiceC");
    Voice* voiceD = new Voice("VoiceD");
    Voice* voiceE = new Voice("VoiceE");
    Voice* voiceF = new Voice("VoiceF");

    scoreA->addStaff(staffA);
    scoreA->addStaff(staffB);
    scoreA->addStaff(staffC);

    scoreB->addStaff(staffD);

    scoreC->addStaff(staffE);
    scoreC->addStaff(staffF);

    staffA->addVoice(voiceA);
    staffA->addVoice(voiceB);
    staffB->addVoice(voiceC);
    staffC->addVoice(voiceD);
    staffD->addVoice(voiceE);
    staffE->addVoice(voiceF);
    staffF->addVoice(voiceA);

    voiceA->addPhrase(phraseA);
    voiceA->addPhrase(phraseB);
    voiceA->addPhrase(phraseC);
    voiceB->addPhrase(phraseD);
    voiceB->addPhrase(phraseE);
    voiceC->addPhrase(phraseF);
    voiceC->addPhrase(phraseG);

    voiceA->setContent("\\voiceTwo \\PhraseB");
    voiceB->setContent("\\voiceOne \\PhraseD \\PhraseE");
    staffA->setContent("\\VoiceB \\VoiceA");

    voiceA->refresh();
    voiceB->refresh();
    staffA->refresh();

    ui->treeWidget->insertTopLevelItem(0,scoreA);
    ui->treeWidget->insertTopLevelItem(1,scoreB);
    ui->treeWidget->insertTopLevelItem(2,scoreC);

    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(onTreeItemClicked(QTreeWidgetItem*,int)));
}

void MainWindow::onTreeItemClicked(QTreeWidgetItem* item, int col) {

    Displayable* d;

    // magic numbers need to turn into constants...
    // don't know where to put them right now...
    switch(item->type()) {
        case 1000: d = (Score*)item; break;
        case 1001: d = (Staff*)item; qDebug() << d->getDisplayLy(); break;
        case 1002: d = (Voice*)item; qDebug() << d->getDisplayLy(); break;
    }

    if(d) {

        // set pixmap label
        if(d->image())
            ui->pixmap->setPixmap(QPixmap::fromImage(*d->image()));
        else
            d->refresh();

        ui->listWidget->clear();
        QList<Phrase*>& list = d->getPhraseList();
        for(int i = 0; i < list.size(); i++)
            new PhraseWidgetListItem(list.at(i),ui->listWidget);
        delete &list;

    }
}
