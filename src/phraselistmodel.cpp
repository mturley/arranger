#include "phraselistmodel.h"

int PhraseListModel::rowCount(const QModelIndex &parent) const {
    return m_phrases.count();
}

QVariant PhraseListModel::data(const QModelIndex &index, int role) const {
    switch(role) {
    case Name :
        return m_phrases.at(index.row())->name(); break;
    case Image :
        return m_phrases.at(index.row())->image(); break;
    }
    return QVariant();
}

QVariant PhraseListModel::headerData(int section,
                                     Qt::Orientation orientation,
                                     int role) const {
    if(section == 0 && role == Qt::DisplayRole)
        return "Phrases";
    return QVariant();
}

Qt::ItemFlags PhraseListModel::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

