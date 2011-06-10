#include "phrasedelegate.h"

#include <QDebug>
#include <QPainter>

#include "phrase.h"
#include "phraselistmodel.h"

PhraseDelegate::PhraseDelegate(QObject *parent)
    : QAbstractItemDelegate(parent) {
}

void PhraseDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const {
    //index.model()->data();
    painter->drawText(option.rect,Qt::AlignCenter,"hey");
    QImage* image = (QImage*)index.model()->data(index,PhraseListModel::Image).toInt();
    painter->drawPixmap(0,option.rect.top(),QPixmap::fromImage(*image));

}

QSize PhraseDelegate::sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
    qDebug() << index.model()->data(index,PhraseListModel::Size).toSize();
    return index.model()->data(index,PhraseListModel::Size).toSize();
}
