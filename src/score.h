#ifndef SCORE_H
#define SCORE_H

#include "idisplayable.h"

class Score : public IDisplayable {
public:
    QString getDisplayLy() const;
    QString getWriteLy() const;
};

#endif // SCORE_H
