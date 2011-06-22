#include "phraseeditor.h"

#include <QDebug>
#include <QHBoxLayout>

#include "lilyhighlighter.h"

PhraseEditor::PhraseEditor(Phrase* phrase,QWidget *parent)
    : QDialog(parent) {

    m_phrase = phrase;

    m_relative      = new QCheckBox();
    m_autoRefresh   = new QCheckBox();

    m_name          = new QLabel("- " + m_phrase->name() + " -");
    m_refreshButton = new QToolButton();
    m_formatButton  = new QToolButton();

    m_editor        = new QTextEdit();
    m_scrollArea    = new QScrollArea();
    m_pixmap        = new QLabel();

    init();
    layout();

    connect(m_refreshButton,SIGNAL(clicked()),m_phrase,SLOT(refresh()));
    connect(m_formatButton,SIGNAL(clicked()),this,SLOT(format()));

    connect(m_editor,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
    connect(m_phrase,SIGNAL(previewChanged()),this,SLOT(updatePixmap()));
    connect(&m_refreshTimer,SIGNAL(timeout()),m_phrase,SLOT(refresh()));
}

void PhraseEditor::show() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase->image()));
    m_pixmap->setFixedSize(m_phrase->size());
    m_phrase = new Phrase(*m_phrase);
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
    m_editor->setPlainText(m_phrase->content());
    new LilyHighlighter(m_editor);
    format();

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

    //toolbuttons->setAlignment(Qt::AlignRight);
    toolbuttons->addWidget(m_name);
    toolbuttons->addWidget(m_formatButton);
    toolbuttons->addWidget(m_refreshButton);

    checkboxes->setAlignment(Qt::AlignLeft);
    checkboxes->addWidget(m_autoRefresh);
    checkboxes->addWidget(m_relative);
}

void PhraseEditor::onTextChanged() {
    m_phrase->setContent(m_editor->toPlainText());
    if(m_autoRefresh->checkState() == Qt::Checked)
        m_refreshTimer.start(1000);
}

void PhraseEditor::updatePixmap() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase->image()));
    m_pixmap->setFixedSize(m_phrase->size());
}

void PhraseEditor::format() {
    QString text = m_phrase->content();

    QStringList tokens;

    QString blockStart = "{[<";
    QString blockEnd   = "}]>";
    QString delimiters = " \n\r";

    QString temp = "";
    for(int i = 0; i < text.size(); i++) {
        int startIndex = i;

        int delimiterType = delimiters.indexOf(text[i]);
        if(delimiterType >= 0) {
            if(temp.size() > 0)
                tokens.append(temp);
            temp.clear();
            continue;
        }

        int blockType = blockStart.indexOf(text[i]);
        if(blockType >= 0)
            while(i < text.size() && text[i] != blockEnd[blockType]) i++;

        temp += text.mid(startIndex,(i - startIndex) + 1);
    }

    QRegExp note("([a-g](?:(?:(?:sharp|is|s)){0,2}|(?:(?:flat|es|f)){0,2})[,']{0,4})(128|64|32|16|8|4|2|1)?");
    QRegExp chord("<(.*)>(128|64|32|16|8|4|2|1)?");

    float   lineValue = 0;
    int     prevValue = 4;
    QString result    = "  ";

    for(int i = 0; i < tokens.size(); i++) {
        qDebug() << tokens[i];

        int noteValue = -1;

        note.indexIn(tokens[i]);

        if(chord.exactMatch(tokens[i])) {
            noteValue = chord.cap(2).toInt();
            noteValue = (noteValue > 0 ? noteValue : prevValue);

            lineValue += 1.0/noteValue;
            prevValue = noteValue;
        }
        else if(note.matchedLength() > 0) {
            noteValue = note.cap(2).toInt();
            noteValue = (noteValue > 0 ? noteValue : prevValue);

            lineValue += 1.0/noteValue;
            prevValue = noteValue;
        }

        result += tokens[i];
        result += " ";

        if(lineValue >= 1) {
            lineValue = 0;
            result += "\n  ";
        }
    }

    m_editor->setText(result);
}
