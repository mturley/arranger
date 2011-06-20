#include "phraselistdelegate.h"

#include <QDebug>
#include <QPainter>

#include "phraselistmodel.h"

PhraseListDelegate::PhraseListDelegate(QObject *parent)
    : QAbstractItemDelegate(parent) { }

void PhraseListDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex &index) const {
    QString name  = index.data(PhraseListModel::Name).toString();
    QImage* image = (QImage*)index.data(PhraseListModel::Image).value<uint>();
    QSize size(50,50);

    if(image)
        size = image->size();

    QPoint nameLocation;
    nameLocation.setX(5);
    nameLocation.setY(option.rect.y() + (option.rect.height() - painter->font().pixelSize()) / 2);

    QPoint imageLocation = option.rect.center();
    imageLocation.setX(100);
    qDebug() << "(option.rect.width() - size.width()) / 2 ==" << option.rect.width() << size.width();
    imageLocation.setY((option.rect.width() - size.width()) / 2);

    painter->drawRect(option.rect);

    //if(image)
    //    painter->drawPixmap(imageLocation,QPixmap::fromImage(*image));

    painter->drawText(nameLocation,name);
}

QSize PhraseListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex &index) const {
    QImage* image = (QImage*)index.data(PhraseListModel::Image).value<uint>();

    return QSize(100,50);
    if(image)
        return image->size();
    return QSize(50,50);
}
