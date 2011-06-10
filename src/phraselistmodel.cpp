#include "phraselistmodel.h"

#include <QDebug>

PhraseListModel::PhraseListModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int PhraseListModel::rowCount(const QModelIndex &parent) const {
    return m_phrases.count();
}

QVariant PhraseListModel::data(const QModelIndex &index, int role) const {
    switch(role) {
    case Name :
        return m_phrases.at(index.row())->name(); break;
    case Image :
        return QVariant::fromValue((int)m_phrases.at(index.row())->image()); break;
    case Size :
        return m_phrases.at(index.row())->size(); break;
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

void PhraseListModel::append(Phrase* phrase) {
    m_phrases.append(phrase);
}
