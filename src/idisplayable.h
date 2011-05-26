#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

// implement IDisplayable if a class needs to be able
// to display itself lilypond data
class IDisplayable {
public:
    virtual ~IDisplayable() {}
    // return lilypond output that can stand alone
    // and be compiled to give a preview of a class
    virtual QString getDisplayLy() = 0;
    // return lilypond output that is meant to work
    // with other classes getDisplayLy
    virtual QString getWriteLy() = 0;
};

#endif // IDISPLAYABLE_H
