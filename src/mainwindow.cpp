#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollBar>

#include "phraselistdelegate.h"
#include "phraselistmodel.h"
#include "phrasewidgetlistitem.h"
#include "phrasewidget.h"
#include "score.h"
#include "staff.h"
#include "voice.h"
#include "phrase.h"

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
    ui->listView->setResizeMode(QListView::Adjust);
    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    PhraseListDelegate* delegate = new PhraseListDelegate();
    PhraseListModel* model       = new PhraseListModel();

    ui->listView->setModel(model);
    ui->listView->setItemDelegate(delegate);

    Phrase* phraseA = new Phrase("PhraseA","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
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

    model->append(phraseA);
    model->append(phraseB);
    model->append(phraseC);
    model->append(phraseD);
    model->append(phraseE);
    model->append(phraseF);
    model->append(phraseG);
    model->append(phraseH);

    new PhraseWidgetListItem(phraseA,ui->listWidget);
    new PhraseWidgetListItem(phraseB,ui->listWidget);
    new PhraseWidgetListItem(phraseC,ui->listWidget);
    new PhraseWidgetListItem(phraseD,ui->listWidget);
    new PhraseWidgetListItem(phraseE,ui->listWidget);
    new PhraseWidgetListItem(phraseF,ui->listWidget);
    new PhraseWidgetListItem(phraseG,ui->listWidget);
    new PhraseWidgetListItem(phraseH,ui->listWidget);

    // test tree models

    Score* scoreA = new Score("Score A");
    Score* scoreB = new Score("Score B");
    Score* scoreC = new Score("Score C");

    Staff* staffA = new Staff("Staff A");
    Staff* staffB = new Staff("Staff B");
    Staff* staffC = new Staff("Staff C");
    Staff* staffD = new Staff("Staff D");
    Staff* staffE = new Staff("Staff E");
    Staff* staffF = new Staff("Staff F");

    Voice* voiceA = new Voice("Voice A");
    Voice* voiceB = new Voice("Voice B");
    Voice* voiceC = new Voice("Voice C");
    Voice* voiceD = new Voice("Voice D");
    Voice* voiceE = new Voice("Voice E");
    Voice* voiceF = new Voice("Voice F");

    scoreA->addStaff(staffA);
    scoreA->addStaff(staffB);
    scoreA->addStaff(staffC);

    scoreB->addStaff(staffD);

    scoreC->addStaff(staffE);
    scoreC->addStaff(staffF);

    staffA->addVoice(voiceA);
    staffB->addVoice(voiceB);
    staffC->addVoice(voiceC);
    staffD->addVoice(voiceD);
    staffE->addVoice(voiceE);
    staffF->addVoice(voiceF);

    ui->treeWidget->insertTopLevelItem(0,scoreA);
    ui->treeWidget->insertTopLevelItem(1,scoreB);
    ui->treeWidget->insertTopLevelItem(2,scoreC);
}
