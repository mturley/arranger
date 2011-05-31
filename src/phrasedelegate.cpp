#include "phrasedelegate.h"

void PhraseDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const {
    //index.model()->data();

}

QSize PhraseDelegate::sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
    return QSize(300,50);
}
