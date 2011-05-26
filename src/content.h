#ifndef CONTENT_H
#define CONTENT_H

#include "idisplayable.h"

class Content : public IDisplayable {
public:
    Content(const QString content) : m_content(content) { }

    void setContent(const QString);

    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QString m_content;
};

#endif // CONTENT_H
