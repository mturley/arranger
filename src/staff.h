#ifndef STAFF_H
#define STAFF_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "voice.h"

class Staff : public Displayable, public QTreeWidgetItem {
public:
    Staff(QString);

    void addVoice(Voice*);

    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QList<Voice*> m_voices;
    QString       m_name;
};

#endif // STAFF_H
