#include "score.h"

Score::Score(QString name)
    : Displayable(name),
      QTreeWidgetItem(1000) {
    this->setText(0,name);
}

void Score::addStaff(Staff* staff) {
    m_staves.append(staff);
    this->addChild(staff);
}

QString Score::getDisplayLy() const {
    return QString();
}

QString Score::getWriteLy() const {
    return QString();
}

QList<Phrase*>& Score::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    for(int i = 0; i < m_staves.size(); i++)
        list->append(m_staves.at(i)->getPhraseList());
    return *list;
}
