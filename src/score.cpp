#include "score.h"

bool Score::append(IChildItem* item) {
    if(item->type() != ChildType::Staff)
        return false;

    m_staves.append((Staff*)item);
    return true;
}

IChildItem* Score::child(int) const {
    return m_staves.at()
}

QString Score::getDisplayLy() const {
    return QString();
}

QString Score::getWriteLy() const {
    return QString();
}
