#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include <QTreeWidgetItem>

#include "displayable.h"

class Phrase;

class Voice : public Displayable,
              public QTreeWidgetItem {
    Q_OBJECT
private:
    static const char* displayTemplate() {
        // %1 : phrases
        // %2 : content
        return "\\version \"2.8.1\"\n"
               "\\paper {\n"
               "  ragged-right = ##t\n"
               "  indent = 0.0\\mm\n"
               "}\n"
               "%1\n"
               "{\n%2\n}\n";
    }
    static const char* writeTemplate() {
        // %1 : phrases
        // %2 : name
        // %3 : content
        return "%1"
               "%2 = \\new Voice {\n%3\n}\n";
    }
public:
    Voice();
    Voice(QString);
    Voice(const Voice&);
    ~Voice();

    void addPhrase(Phrase*);

    QString getDisplayLy() const;
    QString getWriteLy() const;

    QList<Phrase*>& getPhraseList();

    friend QDataStream& operator<<(QDataStream& out, const Voice& voice);
    friend QDataStream& operator>>(QDataStream& in, Voice& voice);

private:
    QList<Phrase*> m_phrases; // available phrases
};

#endif // VOICE_H
