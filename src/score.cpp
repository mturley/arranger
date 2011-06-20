#include "score.h"

Score::Score(QString name)
    : QTreeWidgetItem(1000) {
    m_name = name;
    this->setText(0,m_name);
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
