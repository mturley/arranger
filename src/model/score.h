#ifndef SCORE_H
#define SCORE_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "staff.h"

class Score : public Displayable, public QTreeWidgetItem {
public:
    Score(QString);

    void addStaff(Staff*);

    QString getDisplayLy() const;
    QString getWriteLy() const;

    QList<Phrase*>& getPhraseList();
private:
    QList<Staff*> m_staves;
    QString       m_name;
};

#endif // SCORE_H
