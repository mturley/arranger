#ifndef SCORE_H
#define SCORE_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "staff.h"

class Score : public Displayable, public QTreeWidgetItem {
public:
    Score();
    Score(QString);
    Score(const Score&);
    ~Score();

    void addStaff(Staff*);

    QString getDisplayLy() const;
    QString getWriteLy() const;

    QList<Phrase*>& getPhraseList();

    friend QDataStream& operator<<(QDataStream& out, const Score& score);
    friend QDataStream& operator>>(QDataStream& in, Score& score);

private:
    QList<Staff*> m_staves;
};

#endif // SCORE_H
