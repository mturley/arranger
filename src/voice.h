#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include "idisplayable.h"

class Voice : public QObject, public IDisplayable {
    Q_OBJECT
private:
    static const char* displayTemplate() {
        return "\\version \"2.8.1\"\n"
               "\\paper {\n"
               "  ragged-right = ##t\n"
               "  indent = 0.0\\mm\n"
               "}\n"
               "%1"
               "%2";
    }
    static const char* writeTemplate() {
        return "%1 = \\new Voice %2 {\n%3\n}";
    }
public:
    QString getDisplayLy();
    QString getWriteLy();
};

#endif // VOICE_H
