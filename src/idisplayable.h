#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include "icontent.h"

class QImage;

class IDisplayable : public IContent {
public:
    virtual ~IDisplayable() {}

    virtual void setImage(QImage*) = 0;
};

#endif // IDISPLAYABLE_H
