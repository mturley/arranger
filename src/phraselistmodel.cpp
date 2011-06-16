#include "phraselistmodel.h"

#include <QDebug>

PhraseListModel::PhraseListModel(QObject *parent)
    : QAbstractListModel(parent) { }

int PhraseListModel::rowCount(const QModelIndex&) const {
    return m_phrases.count();
}

QVariant PhraseListModel::data(const QModelIndex &index, int role) const {
    switch(role) {
        case Name:
            return m_phrases.at(index.row())->name(); break;
        case Image:
            return (uint)m_phrases.at(index.row())->image(); break;
    }
    return QVariant();
}

Qt::ItemFlags PhraseListModel::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void PhraseListModel::append(Phrase* phrase) {
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_phrases.append(phrase);
    endInsertRows();
}
