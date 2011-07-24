#include "voice.h"

#include <QDebug>

#include "phrase.h"

Voice::Voice()
    : Displayable(),
      QTreeWidgetItem(1002) {
    this->setText(0,"Uh Oh, need a name");
}

Voice::Voice(QString name)
    : Displayable(name),
      QTreeWidgetItem(1002) {
    this->setText(0,name);
}

Voice::Voice(const Voice& v)
    : Displayable(v),
      QTreeWidgetItem(1002) {
    qDebug() << "Phrases:" << v.m_phrases;
    for(int i = 0; i < v.m_phrases.size(); i++)
        addPhrase(new Phrase(*v.m_phrases.at(i)));
    this->setText(0,name());
}

Voice::~Voice() {
    for(int i = 0; i < m_phrases.size(); i++)
        delete m_phrases.at(i);
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
    return QString(writeTemplate()).arg(phrase_ly,name(),content());
}

QList<Phrase*>& Voice::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    for(int i = 0; i < m_phrases.size(); i++)
        list->append(m_phrases.at(i));
    return *list;
}

QDataStream& operator<<(QDataStream& out, const Voice& voice) {
    voice.Displayable::operator<<(out);
    QList<Phrase> list;
    for(int i = 0; i < voice.m_phrases.size(); i++)
        list.append(*voice.m_phrases.at(i));
    return out << list;
}

QDataStream& operator>>(QDataStream& in, Voice& voice) {
    voice.Displayable::operator>>(in);
    QList<Phrase> list;
    in >> list;
    for(int i = 0; i < list.size(); i++)
        voice.addPhrase(new Phrase(list.at(i)));
    return in;
}
