#ifndef IPARENTITEM_H
#define IPARENTITEM_H

class IChildItem;

class IParentItem {
public:
    virtual ~IParentItem() { }

    virtual bool append(IChildItem*) = 0;
    virtual IChildItem* child(int row) const = 0;
};

#endif // IPARENTITEM_H
