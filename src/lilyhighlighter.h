#ifndef LILYHIGHLIGHTER_H
#define LILYHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class LilyHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    LilyHighlighter(QTextEdit* parent);
protected:
    void highlightBlock(const QString &text);
private:
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> m_highlightingRules;

    QRegExp         m_notePattern;
    QTextCharFormat m_numberFormat;
    QTextCharFormat m_notenameFormat;
    QTextCharFormat m_articulationFormat;
};

#endif // LILYHIGHLIGHTER_H
