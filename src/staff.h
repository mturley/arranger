#ifndef STAFF_H
#define STAFF_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "voice.h"

class Staff : public Displayable, public QTreeWidgetItem {
public:
    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QList<Voice*> m_voices;
};

#endif // STAFF_H
