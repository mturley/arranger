#include "phraseeditor.h"

#include <QDebug>
#include <QHBoxLayout>

PhraseEditor::PhraseEditor(Phrase* phrase,QWidget *parent)
    : QDialog(parent) {

    m_phrase = new Phrase(*phrase);

    m_relative   = new QCheckBox(this);
    m_editor     = new QTextEdit(m_phrase->content(),this);
    m_scrollArea = new QScrollArea(this);
    m_pixmap     = new QLabel();

    QFont font;
    font.setFamily("Andale");
    font.setFixedPitch(true);
    font.setPixelSize(12);
    font.setWeight(1);
    m_editor->setFont(font);

    m_editor->setFixedWidth(200);
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
    QString text = m_editor->toPlainText().trimmed();

    // split on whitespace
    QStringList symbols = text.split(" ");

    QString result = "";

    // line breaks occur at lineValue >= 1
    float lineValue = 0;
    int previousValue = 4;
    // matches a single note, capture note length
    // this is a rough approximation
    QRegExp note("[a-z](?:is|es)?(?:'*|,*)(\\d+)?[^a-z1-9]*");
    // matches a single note, unspecified note length

    result += "  ";
    for(int i = 0; i < symbols.size(); i++) {
        // find symbolValue
        qDebug() << symbols[i];
        // if note matches the symbol
        if(note.indexIn(symbols[i]) >= 0) {
            int noteValue = note.cap(1).toInt() > 0 ? note.cap(1).toInt() : previousValue;
            lineValue += 1.0/noteValue;
            previousValue = noteValue;
            qDebug() << "match";
        }

        result += symbols[i];
        result += " ";

        if(lineValue >= 1) {
            result += "\n  ";
            lineValue = 0;
        }
    }

    m_editor->setText(result);
}
