#include "voice.h"

#include "phrase.h"

Voice::Voice(QString name)
    : QTreeWidgetItem(1002) {
    m_name = name;
    this->setText(0,m_name);
}

void Voice::addPhrase(Phrase* phrase) {
    m_phrases.append(phrase);
}

QString Voice::getDisplayLy() const {
    QString phrase_ly;
    for(int i = 0; i < m_phrases.size(); i++)
        phrase_ly.append(m_phrases.at(i)->getWriteLy());
    return QString(displayTemplate()).arg(phrase_ly,content());
}

QString Voice::getWriteLy() const {
    QString phrase_ly;
    for(int i = 0; i < m_phrases.size(); i++)
        phrase_ly.append(m_phrases.at(i)->getWriteLy());
    return QString(writeTemplate()).arg(phrase_ly,m_name,content());
}

QList<Phrase*>& Voice::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    for(int i = 0; i < m_phrases.size(); i++)
        list->append(m_phrases.at(i));
    return *list;
}
