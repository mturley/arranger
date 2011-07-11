#ifndef PHRASEWIDGET_H
#define PHRASEWIDGET_H

#include <QLabel>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

#include "../model/phrase.h"
#include "phraseeditor.h"

class PhraseWidget : public QWidget {
    Q_OBJECT
public:
    PhraseWidget(Phrase*,QWidget* parent = 0);

    QSize sizeHint() const;
signals:
    void pixmapChanged();
private slots:
    void updatePixmap();
    void openEditor();
private:
    PhraseEditor* m_phraseEditor;
    Phrase*       m_phrase;

    QToolButton*  m_refreshButton;
    QLabel*       m_name;
    QScrollArea*  m_scrollArea;
    QLabel*       m_pixmap;
};

#endif // PHRASEWIDGET_H
