#include "content.h"

#include <QStringList>

void Content::setContent(const QString content) {
    m_content = content;
}

QString Content::getDisplayLy() const {
    QString result;

    QStringList s = m_content.split('\n');
    QStringListIterator i(s);
    while(i.hasNext())
        result += i.next().trimmed().prepend("  ").append('\n');

    return result;
}

QString Content::getWriteLy() const {
    return getDisplayLy();
}
