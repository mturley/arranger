#ifndef ICHILDITEM_H
#define ICHILDITEM_H

class IParentItem;

namespace ChildType {
    enum Type {
        Score,
        Staff,
        Voice
    };
}

class IChildItem {
public:
    virtual ~IChildItem() { }

    virtual ChildType::Type type() = 0;
    virtual IParentItem* parent() = 0;
};

#endif // ICHILDITEM_H
