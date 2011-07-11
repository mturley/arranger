#include "phrasewidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QScrollBar>

#include "../lilytools.h"

PhraseWidget::PhraseWidget(Phrase* phrase,QWidget *parent)
    : QWidget(parent) {

    m_phrase        = phrase;
    m_phraseEditor  = new PhraseEditor(m_phrase);

    m_refreshButton = new QToolButton(this);
    m_name          = new QLabel(m_phrase->name(),this);
    m_scrollArea    = new QScrollArea(this);
    m_pixmap        = new QLabel();

    m_refreshButton->setIcon(QIcon::fromTheme("accessories-text-editor"));

    m_name->setFixedWidth(100);

    m_scrollArea->setWidget(m_pixmap);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if(m_phrase->image())
        m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase->image()));

    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(m_name);
    layout->addWidget(m_refreshButton);
    layout->addWidget(m_scrollArea);

    connect(m_phrase,SIGNAL(previewChanged()),this,SLOT(updatePixmap()));
    connect(m_refreshButton,SIGNAL(clicked()),this,SLOT(openEditor()));
}

QSize PhraseWidget::sizeHint() const {
    QSize sizeHint = QWidget::sizeHint();
    // need a better way to do this...
    // leaving it for the moment
    return QSize(sizeHint.width(),m_scrollArea->height() + 50 + m_scrollArea->horizontalScrollBar()->height());
}

void PhraseWidget::updatePixmap() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase->image()));
    m_pixmap->setFixedSize(m_phrase->size());

    this->resize(this->width(),m_pixmap->height());

    emit pixmapChanged();
}

void PhraseWidget::openEditor() {
    m_phraseEditor->show();
   qDebug() <<  LilyTools::tokenize(m_phrase->content());
}
