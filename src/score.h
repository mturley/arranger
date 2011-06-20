#ifndef SCORE_H
#define SCORE_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "staff.h"

class Score : public Displayable, public QTreeWidgetItem {
public:
    QString getDisplayLy() const;
    QString getWriteLy() const;
private:
    QList<Staff*> m_staves;
};

#endif // SCORE_H
