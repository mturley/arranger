#ifndef PHRASELISTMODEL_H
#define PHRASELISTMODEL_H

#include <QAbstractListModel>

#include "phrase.h"

class PhraseListModel : QAbstractListModel {
public:
    enum Role {
        Name = Qt::UserRole + 1,
        Image
    };

    PhraseListModel(QObject* parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<Phrase*> m_phrases;

};

#endif // PHRASELISTMODEL_H
