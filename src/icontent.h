#ifndef ICONTENT_H
#define ICONTENT_H

class QString;

class IContent {
public:
    virtual ~IContent() {}

    virtual QString getDisplayLy() const = 0;
    virtual QString getWriteLy() const = 0;
};

#endif // ICONTENT_H
