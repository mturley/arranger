#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include "idisplayable.h"
#include "content.h"

class Phrase;

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
    Voice(QString name) : m_name(name), m_content("") {}
    QString getDisplayLy() const;
    QString getWriteLy() const;

private:
    QString        m_name;
    Content        m_content;
    QList<Phrase*> m_phrases; // available phrases
};

#endif // VOICE_H
