#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
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
    ui(new Ui::MainWindow),
    m_selection(0)
{
    ui->setupUi(this);
    init();
    //testModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setResizeMode(QListWidget::Adjust);

    ui->refreshButton->setIconSize(QSize(16,16));
    ui->refreshButton->setIcon(QIcon::fromTheme("view-refresh"));
    ui->formatButton->setIconSize(QSize(16,16));
    ui->formatButton->setIcon(QIcon::fromTheme("format-text-direction-ltr"));

    QFont font;
    font.setFamily("Andale");
    font.setFixedPitch(true);
    font.setPixelSize(12);
    font.setWeight(1);

    ui->contentEdit->setFont(font);

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setPalette(QPalette(Qt::white));


    // connect onTreeItemClicked
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(onTreeItemClicked(QTreeWidgetItem*,int)));

    // connect onTreeContextMenuRequested
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(onTreeContextMenuRequested(QPoint)));

    // connect onContentEditChanged
    connect(ui->contentEdit,SIGNAL(textChanged()),this,SLOT(onContentEditChanged()));

    // connect onNameEditChanged
    connect(ui->nameEdit,SIGNAL(textChanged(QString)),this,SLOT(onNameEditChanged(QString)));

    // connect file menu actions
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(onOpen()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(onSave()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(onSaveAs()));
}

void MainWindow::testModel() {
    Phrase* phraseA = new Phrase("PhraseAAALongNameTotally","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
    Phrase* phraseB = new Phrase("PhraseB","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4");
    Phrase* phraseC = new Phrase("PhraseC","e8 e e e f g f e c' c c d c b a g");
    Phrase* phraseD = new Phrase("PhraseD","f1~ f");
    Phrase* phraseE = new Phrase("PhraseE","<c' e g>1 b8 a g f e d c4 d'2 e2( f4 c4 g8 -> ( a8 g4)");
    Phrase* phraseF = new Phrase("PhraseF","d2 e2( f4 c4 g8 a8 g4) c'1 b8 a g f e d c4 c'1 b8 a g f e d c4");
    Phrase* phraseG = new Phrase("PhraseG","e8 e e e f g f e c' c c d c b a g");
    Phrase* phraseH = new Phrase("PhraseH","f1~ f");

    //phraseA->refresh();
    //phraseB->refresh();
    //phraseC->refresh();
    //phraseD->refresh();
    //phraseE->refresh();
    //phraseF->refresh();
    //phraseG->refresh();
    //phraseH->refresh();

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

    //voiceA->refresh();
    //voiceB->refresh();
    //staffA->refresh();

    ui->treeWidget->insertTopLevelItem(0,scoreA);
    ui->treeWidget->insertTopLevelItem(1,scoreB);
    ui->treeWidget->insertTopLevelItem(2,scoreC);
}

void MainWindow::onTreeItemClicked(QTreeWidgetItem* item, int col) {

    Displayable* d = 0;

    // magic numbers need to turn into constants...
    // don't know where to put them right now...
    switch(item->type()) {
        case 1000: d = (Score*)item; break;
        case 1001: d = (Staff*)item; break;
        case 1002: d = (Voice*)item; break;
    }

    if(d) {
        disconnect(m_selection);

        // set m_selection
        m_selection = d;

        connect(ui->refreshButton,SIGNAL(clicked()),m_selection,SLOT(refresh()));
        connect(m_selection,SIGNAL(previewChanged()),this,SLOT(onRefreshButtonClicked()));

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

        // set contentEdit
        ui->contentEdit->setPlainText(d->content());

        // set nameEdit
        ui->nameEdit->setText(d->name());
    }
}

void MainWindow::onTreeContextMenuRequested(const QPoint& pos) {
    qDebug() << "Context Menu requested at" << pos;
}

void MainWindow::onContentEditChanged() {
    qDebug() << "onContentEditChanged";
    if(m_selection) {
        m_selection->setContent(ui->contentEdit->toPlainText());
    }
}

void MainWindow::onNameEditChanged(QString s) {
    qDebug() << "onNameEditChanged :" << s;
    if(m_selection) {
        ui->treeWidget->currentItem()->setText(0,s);
        m_selection->setName(s);
    }
}

void MainWindow::onRefreshButtonClicked() {
    if(m_selection) {
        if(m_selection->image())
            ui->pixmap->setPixmap(QPixmap::fromImage(*m_selection->image()));
        else
            m_selection->refresh();
    }
}

void MainWindow::onNew() {

}

void MainWindow::onOpen() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Arranger File", QDir::home().absolutePath(), "Arranger Files (*.arr)");
    qDebug() << "Opening:" << fileName;

    if(fileName.isNull())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
        return;

    qDebug() << "Creating data stream...";
    QDataStream in(&file);

    QList<Score> scores;

    qDebug() << "Reading data...";
    in >> scores;

    qDebug() << "Setting data...";
    qDebug() << "  " << scores.size() << "scores";

    qDebug() << "about to clear";
    ui->treeWidget->clear();
    qDebug() << "treeWidget is clear";
    for(int i = 0; i < scores.size(); i++) {
        qDebug() << "inserting score" << i;
        ui->treeWidget->insertTopLevelItem(i,new Score(scores.at(i)));
    }

    m_fileName = fileName;

    qDebug() << "Done.";
}

void MainWindow::onSave() {
    if(m_fileName.isNull()) {
        onSaveAs();
        return;
    }

    QFile file(m_fileName);

    qDebug() << "Opening:" << m_fileName;
    if(!file.open(QIODevice::WriteOnly))
        return;

    qDebug() << "Creating data stream...";
    QDataStream out(&file);

    qDebug() << "Writing data..." << ui->treeWidget->topLevelItemCount();
    QList<Score> list;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        list.append(*(Score*)ui->treeWidget->topLevelItem(i));
    out << list;

    qDebug() << "Done.";
}

void MainWindow::onSaveAs() {
    m_fileName = QFileDialog::getSaveFileName(this, "Save File",
                                              QDir::home().absolutePath(),
                                              "Arranger Files (*.arr)");
    onSave();
}
