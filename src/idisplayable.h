#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include "icontent.h"

class QImage;

namespace PreviewFlags {
    enum PreviewFlag {
        Recent  = 0x1,          // is preview up to date?
        Error   = 0x2,          // generating preview resulted in error
        Loading = 0x4           // loading preview
    };
}

class IDisplayable : public IContent {
public:
    virtual ~IDisplayable() {}

    virtual bool testFlag(PreviewFlags::PreviewFlag) = 0;
    virtual void setImage(QImage*) = 0;
};

#endif // IDISPLAYABLE_H
