#include "phraselistdelegate.h"

#include <QDebug>
#include <QPainter>

#include "phraselistmodel.h"

PhraseListDelegate::PhraseListDelegate(QObject *parent)
    : QAbstractItemDelegate(parent) { }

void PhraseListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString name  = index.data(PhraseListModel::Name).toString();
    QImage* image = (QImage*)index.data(PhraseListModel::Image).value<uint>();

    painter->drawText(option.rect,name);

    if(image)
        painter->drawPixmap(option.rect.topLeft(),QPixmap::fromImage(*image));
}

QSize PhraseListDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex &index) const {
    QImage* image = (QImage*)index.data(PhraseListModel::Image).value<uint>();

    if(image)
        return image->size();
    return QSize(50,50);
}
