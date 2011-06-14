#include "lilyhighlighter.h"

LilyHighlighter::LilyHighlighter(QTextEdit *parent)
    : QSyntaxHighlighter(parent) {

    m_notePattern = QRegExp("\\b[a-z](?:is|es)\\b");
}

void LilyHighlighter::highlightBlock(const QString &text) {

}
