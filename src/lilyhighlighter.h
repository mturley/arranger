#ifndef LILYHIGHLIGHTER_H
#define LILYHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class LilyHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    LilyHighlighter(QTextEdit* parent);
protected:
    void highlightBlock(const QString &text);
};

#endif // LILYHIGHLIGHTER_H
