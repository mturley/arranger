#ifndef PHRASELISTMODEL_H
#define PHRASELISTMODEL_H

#include <QAbstractListModel>

#include "phrase.h"

class PhraseListModel : public QAbstractListModel {
public:
    enum Roles {
        Name = Qt::UserRole + 1,
        Image
    };
public:
    PhraseListModel(QObject* parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void append(Phrase*);

private:
    QList<Phrase*> m_phrases;

};

#endif // PHRASELISTMODEL_H
