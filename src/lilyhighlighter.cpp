#include "lilyhighlighter.h"

LilyHighlighter::LilyHighlighter(QTextEdit *parent)
    : QSyntaxHighlighter(parent) {

    HighlightingRule rule;

    rule.pattern = QRegExp("");
    rule.format = m_notenameFormat;
    m_highlightingRules.append(rule);

    rule.format = m_notedurationFormat;
    m_highlightingRules.append(rule);

    rule.format = m_articulationFormat;
    m_highlightingRules.append(rule);

}

void LilyHighlighter::highlightBlock(const QString &text) {

}
