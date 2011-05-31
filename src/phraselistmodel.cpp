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
