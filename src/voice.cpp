#include "voice.h"

#include "phrase.h"

ChildType::Type Voice::type() {
    return ChildType::Voice;
}

bool Voice::append(IChildItem* item) {
    if(item->type() != ChildType::Phrase)
        return false;

    m_phrases.append((Phrase*)item);
    return true;
}

IChildItem* Voice::child(int index) const {
    return m_phrases.at(index);
}

QString Voice::getDisplayLy() const {
    return QString();
}

QString Voice::getWriteLy() const {
    return QString();
}
