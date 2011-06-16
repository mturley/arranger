#ifndef STAFF_H
#define STAFF_H

#include "idisplayable.h"
#include "iparentitem.h"
#include "ichilditem.h"
#include "voice.h"

class Staff : public IDisplayable,
              public IParentItem,
              public IChildItem {
public:
    ChildType::Type type();
    bool append(IChildItem*);
    IChildItem* child(int) const;

    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QList<Voice*> m_voices;
};

#endif // STAFF_H
