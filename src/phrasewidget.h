#ifndef PHRASEWIDGET_H
#define PHRASEWIDGET_H

#include <QLabel>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

#include "phrase.h"

class PhraseWidget : public QWidget {
public:
    PhraseWidget(Phrase*,QWidget* parent = 0);

private:
    Phrase*      m_phrase;
    QToolButton* m_refreshButton;
    QLabel*      m_name;
    QScrollArea* m_scrollArea;
    QLabel*      m_pixmap;
};

#endif // PHRASEWIDGET_H
