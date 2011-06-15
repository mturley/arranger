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

    QTextCharFormat m_notenameFormat;
    QTextCharFormat m_notedurationFormat;
    QTextCharFormat m_articulationFormat;
};

#endif // LILYHIGHLIGHTER_H
