#include "phrasewidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QScrollBar>

PhraseWidget::PhraseWidget(Phrase* phrase,QWidget *parent)
    : QWidget(parent) {

    m_phrase = phrase;

    m_refreshButton = new QToolButton(this);
    m_name          = new QLabel("Label",this);
    m_scrollArea    = new QScrollArea(this);
    m_pixmap        = new QLabel();

    m_refreshButton->setIcon(QIcon::fromTheme("accessories-text-editor"));

    m_name->setFixedWidth(100);
    m_name->setText(m_phrase->name());

    m_scrollArea->setWidget(m_pixmap);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(m_name);
    layout->addWidget(m_refreshButton);
    layout->addWidget(m_scrollArea);

    connect(m_phrase,SIGNAL(pixmapChanged()),this,SLOT(updatePixmap()));
}

QSize PhraseWidget::sizeHint() const {
    QSize sizeHint = QWidget::sizeHint();
    //return QSize(sizeHint.width(),m_scrollArea->height());
    qDebug() << m_pixmap->height() << m_scrollArea->height() << this->height();
    return QSize(sizeHint.width(),m_scrollArea->height() + 50 + m_scrollArea->horizontalScrollBar()->height());
}

void PhraseWidget::updatePixmap() {
    m_pixmap->setPixmap(QPixmap::fromImage(*m_phrase->image()));
    m_pixmap->setFixedSize(m_phrase->size());
    this->resize(this->width(),m_pixmap->height());
    emit pixmapChanged();
}
