#include "lilyhighlighter.h"

#include <QDebug>

LilyHighlighter::LilyHighlighter(QTextEdit *parent)
    : QSyntaxHighlighter(parent) {

    HighlightingRule rule;

    m_notenameFormat.setForeground(Qt::gray);
    rule.format = m_notenameFormat;
    m_highlightingRules.append(rule);

    rule.format = m_notedurationFormat;
    m_highlightingRules.append(rule);

    rule.format = m_articulationFormat;
    m_highlightingRules.append(rule);

}

void LilyHighlighter::highlightBlock(const QString &text) {
    //qDebug() << "highlightBlock";
    QRegExp lilyNote("([a-g](?:(?:(?:sharp|is|s)){0,2}|(?:(?:flat|es|f)){0,2}))([,']{0,4})(128|64|32|16|8|4|2|1)?");

    QTextCharFormat name;
    QTextCharFormat position;
    QTextCharFormat duration;

    name.setForeground(Qt::black);
    duration.setFontWeight(3);

    position.setForeground(Qt::darkRed);

    duration.setForeground(Qt::blue);
    duration.setFontWeight(5);


    int pos = 0;

    while(pos >= 0) {
        pos = lilyNote.indexIn(text,pos);
        setFormat(lilyNote.pos(1),lilyNote.cap(1).size(),name); // note name
        setFormat(lilyNote.pos(2),lilyNote.cap(2).size(),position); // note position
        setFormat(lilyNote.pos(3),lilyNote.cap(3).size(),duration); // note duration
        pos += lilyNote.cap(0).size();
    }

}
