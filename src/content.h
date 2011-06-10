#ifndef CONTENT_H
#define CONTENT_H

#include <QString>

#include "icontent.h"

class Content : public IContent {
public:
    Content(const QString& content) : m_content(content) { }

    void setContent(const QString&);

    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QString m_content;
};

#endif // CONTENT_H
