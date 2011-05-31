#ifndef PHRASEDELEGATE_H
#define PHRASEDELEGATE_H

#include <QAbstractItemDelegate>

class PhraseDelegate : public QAbstractItemDelegate {
public:
    PhraseDelegate(QObject* parent = 0);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
};

#endif // PHRASEDELEGATE_H
