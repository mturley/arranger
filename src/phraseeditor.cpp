#include "phraseeditor.h"
#include <QPainter>
#include <QDebug>

PhraseEditor::PhraseEditor(Phrase* a_phrase,QGraphicsObject *parent)
    : QGraphicsObject(parent),
      m_phrase(a_phrase) {
    m_item_name    = new QGraphicsSimpleTextItem(this);
    m_item_pixmap  = new QGraphicsPixmapItem(this);
    m_text_edit    = new QTextEdit();
    m_text_edit_proxy = new QGraphicsProxyWidget(this);

    m_item_name->setText(m_phrase->name());
    updatePixmap();
    m_text_edit->setText(m_phrase->content());
    QFont* font = new QFont();
    font->setStyleHint(QFont::Monospace);
    font->setFamily(font->defaultFamily());
    font->setPointSize(10);
    m_text_edit->setFont(*font);
    m_text_edit_proxy->setWidget(m_text_edit);

    connect(m_text_edit,SIGNAL(textChanged()),this,SLOT(updateContent()));
    connect(m_phrase,SIGNAL(pixmapChanged()),this,SLOT(updatePixmap()));
}

QRectF PhraseEditor::boundingRect() const {
    return QRectF(0,0,m_item_pixmap->pixmap().width(),
                      m_item_pixmap->pixmap().height());
}

void PhraseEditor::paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*) {
}

void PhraseEditor::updatePixmap() {
    m_item_pixmap->setPixmap(*m_phrase->pixmap());
    // horizontal layout
    m_item_name->setX(0 + m_item_pixmap->boundingRect().width()/2 - m_item_name->boundingRect().width()/2);
    m_text_edit_proxy->setX(0 + m_item_pixmap->boundingRect().width()/2 - m_text_edit_proxy->boundingRect().width()/2);

    // vertical layout
    m_item_pixmap->setY(0 + m_item_name->boundingRect().height());
    m_text_edit_proxy->setY(m_item_pixmap->y() + m_item_pixmap->boundingRect().height());
}

void PhraseEditor::updateContent() {
    QString content = m_text_edit->toPlainText();

    //if(!content.endsWith(' '))
    //    return;

    m_phrase->setContent(content);
    m_phrase->refresh();
}
