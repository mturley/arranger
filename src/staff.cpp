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
    return QString();
}

QString Staff::getWriteLy() const {
    return QString();
}
