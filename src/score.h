#ifndef SCORE_H
#define SCORE_H

#include "idisplayable.h"
#include "iparentitem.h"
#include "ichilditem.h"
#include "staff.h"

class Score : public IDisplayable,
              public IParentItem {
public:
    bool append(IChildItem*);
    IChildItem* child(int) const;

    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QList<Staff*> m_staves;
};

#endif // SCORE_H
