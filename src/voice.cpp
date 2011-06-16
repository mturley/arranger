#include "voice.h"

#include "phrase.h"

ChildType::Type Voice::type() {
    return ChildType::Voice;
}

QString Voice::getDisplayLy() const {
    return QString();
}

QString Voice::getWriteLy() const {
    return QString();
}
