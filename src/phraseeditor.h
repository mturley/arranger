#ifndef PHRASEEDITOR_H
#define PHRASEEDITOR_H

#include "phrase.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QTextEdit>
#include <QGraphicsProxyWidget>

class PhraseEditor : public QGraphicsObject {
    Q_OBJECT
public:
    PhraseEditor(Phrase*,QGraphicsObject* parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);

public slots:
    void updatePixmap();
    void updateContent();

private:
    Phrase*                  m_phrase;
    QGraphicsSimpleTextItem* m_item_name;
    QGraphicsPixmapItem*     m_item_pixmap;
    QTextEdit*               m_text_edit;
    QGraphicsProxyWidget*    m_text_edit_proxy;
};

#endif // PHRASEEDITOR_H
