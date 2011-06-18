#include "score.h"

bool Score::append(IChildItem* item) {
    if(item->type() != ChildType::Staff)
        return false;

    m_staves.append((Staff*)item);
    return true;
}

IChildItem* Score::child(int index) const {
    return m_staves.at(index);
}

bool Score::testFlag(PreviewFlags::PreviewFlag) {
    return false;
}

void Score::setImage(QImage*) {
}

QString Score::getDisplayLy() const {
    return QString();
}

QString Score::getWriteLy() const {
    return QString();
}
