#include "phraselistdelegate.h"

#include <QDebug>
#include <QFontDatabase>
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
    nameLocation.setY(option.rect.y() + painter->font().pointSize());

    QPoint imageLocation = option.rect.center();
    imageLocation.setX(20);
    imageLocation.setY(option.rect.y() + painter->font().pointSize() + 5);

    //painter->drawRect(option.rect);

    painter->setFont(QFont("Liberation Serif"));
    //qDebug() << QFontDatabase().families(QFontDatabase::Latin);
    painter->drawText(nameLocation,name);

    if(image)
        painter->drawPixmap(imageLocation,QPixmap::fromImage(*image));
}

QSize PhraseListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex &index) const {
    QImage* image = (QImage*)index.data(PhraseListModel::Image).value<uint>();

    if(image) {
        QSize size(image->size());
        size.setHeight(size.height() + option.font.pointSize() + 5);
        return size;
    }
    return QSize(200,80);
}
