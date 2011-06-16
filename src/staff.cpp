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

QString Staff::getDisplayLy() const {
    return QString();
}

QString Staff::getWriteLy() const {
    return QString();
}
