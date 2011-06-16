#ifndef PHRASELISTDELEGATE_H
#define PHRASELISTDELEGATE_H

#include <QAbstractItemDelegate>

class PhraseListDelegate : public QAbstractItemDelegate {
public:
    PhraseListDelegate(QObject* parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PHRASELISTDELEGATE_H
