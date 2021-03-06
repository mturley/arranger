#ifndef STAFF_H
#define STAFF_H

#include <QTreeWidgetItem>

#include "displayable.h"
#include "voice.h"

class Staff : public Displayable, public QTreeWidgetItem {
    static const char* displayTemplate() {
        // %1 : phrases
        // %2 : content
        return "\\version \"2.8.1\"\n"
               "\\paper {\n"
               "  ragged-right = ##t\n"
               "  indent = 0.0\\mm\n"
               "  page-count = 1\n"
               "}\n"
               "%1\n"
               "\\new Staff <<\n%2\n>>\n";
    }
    static const char* writeTemplate() {
        // %1 : voices
        // %2 : name
        // %3 : content
        return "%1"
               "%2 = \\new Staff <<\n%3\n>>\n";
    }
public:
    Staff();
    Staff(QString);
    Staff(const Staff&);
    ~Staff();

    void addVoice(Voice*);

    QString getDisplayLy() const;
    QString getWriteLy() const;

    QList<Phrase*>& getPhraseList();

    friend QDataStream& operator<<(QDataStream& out, const Staff& staff);
    friend QDataStream& operator>>(QDataStream& in, Staff& staff);

private:
    QList<Voice*> m_voices;
};

#endif // STAFF_H
