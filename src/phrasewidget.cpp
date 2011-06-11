#include "phrasewidget.h"

PhraseWidget::PhraseWidget(Phrase* phrase,QWidget *parent)
    : QWidget(parent) {

    m_phrase = phrase;

    m_refreshButton = new QToolButton(this);
    m_name          = new QLabel("Label",this);
    m_scrollArea    = new QScrollArea(this);
    m_pixmap        = new QLabel();

    m_scrollArea->setWidget(m_pixmap);
}
