#include "staff.h"

ChildType::Type Staff::type() {
    return ChildType::Staff;
}

bool Staff::append(IChildItem* item) {
    if(item->type() != ChildType::Voice)
        return false;

    m_voices.append((Voice*)item);
    return true;
}

IChildItem* Staff::child(int index) const {
    return m_voices.at(index);
}

QString Staff::getDisplayLy() const {
    return QString();
}

QString Staff::getWriteLy() const {
    return QString();
}
