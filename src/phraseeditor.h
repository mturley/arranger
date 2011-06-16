#ifndef PHRASEEDITOR_H
#define PHRASEEDITOR_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>

#include "phrase.h"

class PhraseEditor : public QDialog {
    Q_OBJECT
public:
    PhraseEditor(Phrase*,QWidget* parent = 0);
private slots:
    void onTextChanged();
    void updatePixmap();
    void format();
private:
    Phrase*      m_phrase;
    QCheckBox*   m_relative;
    QTextEdit*   m_editor;
    QLabel*      m_pixmap;
    QScrollArea* m_scrollArea;

};

#endif // PHRASEEDITOR_H
