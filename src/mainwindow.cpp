#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    PhraseListDelegate* delegate = new PhraseListDelegate();
    PhraseListModel* model       = new PhraseListModel();

    ui->listView->setModel(model);
    ui->listView->setItemDelegate(delegate);

    Phrase* phrase1 = new Phrase("PhraseI","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
    Phrase* phrase2 = new Phrase("PhraseII","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4");
    Phrase* phrase3 = new Phrase("PhraseIII","e8 e e e f g f e c' c c d c b a g");
    Phrase* phrase4 = new Phrase("PhraseIV","f1~ f");

    phrase1->refresh();
    phrase2->refresh();
    phrase3->refresh();
    phrase4->refresh();

    model->append(phrase1);
    model->append(phrase2);
    model->append(phrase3);
    model->append(phrase4);

    new PhraseWidgetListItem(phrase1,ui->listWidget);
    new PhraseWidgetListItem(phrase2,ui->listWidget);
    new PhraseWidgetListItem(phrase3,ui->listWidget);
    new PhraseWidgetListItem(phrase4,ui->listWidget);

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
