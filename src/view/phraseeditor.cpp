#include "phraseeditor.h"

#include <QDebug>
#include <QHBoxLayout>

#include "../lilyhighlighter.h"
#include "../lilytools.h"

PhraseEditor::PhraseEditor(Phrase* phrase,QWidget *parent)
    : QDialog(parent) {
    m_phrase_original = phrase;
    m_phrase_copy     = new Phrase(*m_phrase_original);

    m_relative        = new QCheckBox();
    m_autoRefresh     = new QCheckBox();

    m_name            = new QLabel();
    m_refreshButton   = new QToolButton();
    m_formatButton    = new QToolButton();

    m_editor          = new QTextEdit();
    m_scrollArea      = new QScrollArea();
    m_pixmap          = new QLabel();

    init();
    layout();

    connect(m_refreshButton,SIGNAL(clicked()),m_phrase_copy,SLOT(refresh()));

    connect(m_editor,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
    connect(m_phrase_copy,SIGNAL(previewChanged()),this,SLOT(updatePixmap()));
    connect(&m_refreshTimer,SIGNAL(timeout()),m_phrase_copy,SLOT(refresh()));
}

void PhraseEditor::show() {
    m_name->setText("- " + m_phrase_copy->name() + " -");
    m_phrase_copy->refresh();

    QDialog::show();
}

void PhraseEditor::init() {
    m_refreshTimer.setSingleShot(true);

    m_relative->setText("Relative");
    m_relative->setChecked(true);
    m_autoRefresh->setText("Auto-Refresh");
    m_autoRefresh->setChecked(false);

    m_refreshButton->setIconSize(QSize(16,16));
    m_refreshButton->setIcon(QIcon::fromTheme("view-refresh"));
    m_formatButton->setIconSize(QSize(16,16));
    m_formatButton->setIcon(QIcon::fromTheme("format-text-direction-ltr"));

    QFont font;
    font.setFamily("Andale");
    font.setFixedPitch(true);
    font.setPixelSize(12);
    font.setWeight(1);

    m_editor->setFont(font);
    m_editor->setFixedWidth(200);
    m_editor->setPlainText(m_phrase_copy->content());
    new LilyHighlighter(m_editor);

    m_scrollArea->setWidget(m_pixmap);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setPalette(QPalette(Qt::white));

    this->setFixedWidth(800);
    this->setFixedHeight(400);
}

void PhraseEditor::layout() {
    QHBoxLayout* layout = new QHBoxLayout(this);
    QVBoxLayout* editor = new QVBoxLayout();
    QVBoxLayout* viewer = new QVBoxLayout();

    QHBoxLayout* toolbuttons = new QHBoxLayout();
    QHBoxLayout* checkboxes  = new QHBoxLayout();

    layout->addLayout(editor);
    layout->addLayout(viewer);

    editor->addLayout(toolbuttons);
    editor->addWidget(m_editor);

    viewer->addLayout(checkboxes);
    viewer->addWidget(m_scrollArea);

    toolbuttons->addWidget(m_name);
    toolbuttons->addWidget(m_formatButton);
    toolbuttons->addWidget(m_refreshButton);

    checkboxes->setAlignment(Qt::AlignLeft);
    checkboxes->addWidget(m_autoRefresh);
    checkboxes->addWidget(m_relative);
}

void PhraseEditor::onTextChanged() {
    m_phrase_copy->setContent(m_editor->toPlainText());
    if(m_autoRefresh->checkState() == Qt::Checked)
        m_refreshTimer.start(1000);
}

void PhraseEditor::updatePixmap() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase_copy->image()));
    m_pixmap->setFixedSize(m_phrase_copy->size());
}
