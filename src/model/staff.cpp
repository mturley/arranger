#include <QDebug>

#include "staff.h"

Staff::Staff()
    : Displayable(),
      QTreeWidgetItem(1001) {
    this->setText(0,"Unnamed Staff");
}

Staff::Staff(QString name)
    : Displayable(name),
      QTreeWidgetItem(1001) {
    this->setText(0,name);
}

Staff::Staff(const Staff& s)
    : Displayable(s),
      QTreeWidgetItem(1001) {
    qDebug() << "Voices:" << s.m_voices;
    for(int i = 0; i < s.m_voices.size(); i++)
        addVoice(new Voice(*s.m_voices.at(i)));
    this->setText(0,name());
}

Staff::~Staff() {
    for(int i = 0; i < m_voices.size(); i++)
        delete m_voices.at(i);
}

void Staff::addVoice(Voice* voice) {
    m_voices.append(voice);
    this->addChild(voice);
}

QString Staff::getDisplayLy() const {
    QString voice_ly;
    for(int i = 0; i < m_voices.size(); i++)
        voice_ly.append(m_voices.at(i)->getWriteLy());
    return QString(displayTemplate()).arg(voice_ly,content());
}

QString Staff::getWriteLy() const {
    return QString();
}

QList<Phrase*>& Staff::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    for(int i = 0; i < m_voices.size(); i++)
        list->append(m_voices.at(i)->getPhraseList());
    return *list;
}

QDataStream& operator<<(QDataStream& out, const Staff& staff) {
    staff.Displayable::operator<<(out);
    QList<Voice> list;
    for(int i = 0; i < staff.m_voices.size(); i++)
        list.append(*staff.m_voices.at(i));
    return out << list;
}

QDataStream& operator>>(QDataStream& in, Staff& staff) {
    staff.Displayable::operator>>(in);
    QList<Voice> list;
    in >> list;
    for(int i = 0; i < list.size(); i++)
        staff.addVoice(new Voice(list.at(i)));
    return in;
}
