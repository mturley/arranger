#include "staff.h"

Staff::Staff(QString name)
    : QTreeWidgetItem(1001) {
    m_name = name;
    this->setText(0,m_name);
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
