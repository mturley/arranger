#include "phraseeditor.h"

#include <QDebug>
#include <QHBoxLayout>

#include "lilyhighlighter.h"

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
    connect(m_formatButton,SIGNAL(clicked()),this,SLOT(format()));

    connect(m_editor,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
    connect(m_phrase_copy,SIGNAL(previewChanged()),this,SLOT(updatePixmap()));
    connect(&m_refreshTimer,SIGNAL(timeout()),m_phrase_copy,SLOT(refresh()));
}

void PhraseEditor::show() {
    m_name->setText("- " + m_phrase_copy->name() + " -");
    m_phrase_copy->refresh();

    format();

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
    //m_phrase_copy->setContent(m_editor->toPlainText());
    if(m_autoRefresh->checkState() == Qt::Checked)
        m_refreshTimer.start(1000);
}

void PhraseEditor::updatePixmap() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase_copy->image()));
    m_pixmap->setFixedSize(m_phrase_copy->size());
}

void PhraseEditor::format() {
    QString text = m_phrase_copy->content();
    qDebug() << text;

    // first, tokenize
    // this should be separated into a function

    QStringList tokens;

    QString blockStart = "{[<";
    QString blockEnd   = "}]>";
    QString delimiters = " \n\r";

    QString temp = "";
    for(int i = 0; i < text.size(); i++) {
        // add token if we hit a delimiter
        int delimiterType = delimiters.indexOf(text[i]);
        if(delimiterType >= 0) {
            if(temp.size() >= 0) {
                tokens.append(temp);
                temp.clear();
            }
            continue;
        }

        // first, separate out blocks
        int blockType = blockStart.indexOf(text[i]);
        if(blockType >= 0) {
            if(blockType == 0) {
                // unhandled
            }
            if(blockType == 1) {
                // unhandled
            }
            if(blockType == 2) {
                while(i < text.size() && text[i] != blockEnd[blockType])
                    temp += text[i++];
                temp += text[i];
                continue;
            }
        }

        temp += text[i];
    }
    if(temp.size() >= 0) {
        tokens.append(temp);
        temp.clear();
    }

    // now re-create

    QRegExp note("([a-g](?:(?:(?:sharp|is|s)){0,2}|(?:(?:flat|es|f)){0,2})[,']{0,4})(128|64|32|16|8|4|2|1)?");
    QRegExp chord("<(.*)>(128|64|32|16|8|4|2|1)?");

    float   lineValue = 0;
    int     prevValue = 4;
    QString result    = "  ";

    for(int i = 0; i < tokens.size(); i++) {
        //qDebug() << tokens[i];
        int noteValue = -1;

        note.indexIn(tokens[i]);

        // determine the note value of a token
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

        // add the token to the string
        result += tokens[i];
        result += " ";

        // break the line if value exceeds 1
        if(lineValue >= 1) {
            lineValue = 0;
            result += "\n  ";
        }
    }

    qDebug() << result;
    m_editor->setText(result);
}
