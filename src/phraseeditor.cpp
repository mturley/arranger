#include "phraseeditor.h"

#include <QDebug>
#include <QHBoxLayout>

PhraseEditor::PhraseEditor(Phrase* phrase,QWidget *parent)
    : QDialog(parent) {

    m_phrase = new Phrase(*phrase);

    m_relative   = new QCheckBox(this);
    m_editor     = new QTextEdit(this);
    m_scrollArea = new QScrollArea(this);
    m_pixmap     = new QLabel();

    QFont font;
    font.setFamily("Andale");
    font.setFixedPitch(true);
    font.setPixelSize(12);
    font.setWeight(1);
    m_editor->setFont(font);

    m_editor->setFixedWidth(200);
    m_editor->setPlainText(m_phrase->content());
    format();

    m_scrollArea->setWidget(m_pixmap);
    m_scrollArea->setWidgetResizable(true);

    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(m_editor);
    layout->addWidget(m_scrollArea);

    this->setFixedWidth(800);
    this->setFixedHeight(400);
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
