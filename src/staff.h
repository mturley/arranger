#ifndef STAFF_H
#define STAFF_H

#include "idisplayable.h"

class Staff : public IDisplayable {
public:
    QString getDisplayLy() const;
    QString getWriteLy() const;
};

#endif // STAFF_H
