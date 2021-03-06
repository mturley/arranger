#ifndef PHRASE_H
#define PHRASE_H

#include <QObject>
#include <QSize>
#include <QString>

#include "displayable.h"

class QImage;
class QPixmap;
class Voice;

class Phrase : public Displayable {
    Q_OBJECT
private:
    static const char* displayTemplate() {
        // %1 : relative pitch
        // %2 : content
        return "\\version \"2.8.1\"\n"
               "\\paper {\n"
               "  ragged-right = ##t\n"
               "  indent = 0.0\\mm\n"
               "}\n"
               "\\relative %1 {\n"
               "%2"
               "}\n";
    }
    static const char* writeTemplate() {
        // %1 : name
        // %2 : content
        return "%1 = {\n%2\n}\n";
    }
public:
    Phrase();
    Phrase(QString,QString = "");
    Phrase(const Phrase&);
    ~Phrase();

public slots:
    void setStderr (const QString);

public:
    const QString stderr() const;

    QString getDisplayLy() const;
    QString getWriteLy() const;

    QList<Phrase*>& getPhraseList();

    //QDataStream& operator<<(QDataStream& s) const;
    //QDataStream& operator>>(QDataStream& s);

signals:
    void stderrChanged();

private:
    QString      m_stderr;        // lilypond output
    bool         m_relative_flag; // notes are relative or absolute
    QString      m_relative_note; // relative note [a-g](is|es)('*|,*)
};

#endif // PHRASE_H
