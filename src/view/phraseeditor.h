#ifndef PHRASEEDITOR_H
#define PHRASEEDITOR_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QTimer>
#include <QToolButton>

#include "../model/phrase.h"

class PhraseEditor : public QDialog {
    Q_OBJECT
public:
    PhraseEditor(Phrase*,QWidget* parent = 0);

public slots:
    void show();
private:
    void init();
    void layout();
    void reset();
private slots:
    void onTextChanged();
    void updatePixmap();
private:
    Phrase*      m_phrase_original;
    Phrase*      m_phrase_copy;
    QCheckBox*   m_relative;
    QCheckBox*   m_autoRefresh;

    QLabel*      m_name;
    QToolButton* m_refreshButton;
    QToolButton* m_formatButton;

    QTextEdit*   m_editor;
    QLabel*      m_pixmap;
    QScrollArea* m_scrollArea;

    QTimer       m_refreshTimer;

};

#endif // PHRASEEDITOR_H
