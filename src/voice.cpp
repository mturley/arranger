#include "voice.h"

#include "phrase.h"

Voice::Voice(QString name)
    : QTreeWidgetItem(1002) {
    m_name = name;
    this->setText(0,m_name);
}

QString Voice::getDisplayLy() const {
    return QString();
}

QString Voice::getWriteLy() const {
    return QString();
}
