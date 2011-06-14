#ifndef PHRASE_H
#define PHRASE_H

#include <QObject>
#include <QSize>
#include <QString>

#include "idisplayable.h"
#include "content.h"

class QImage;
class QPixmap;
class Voice;

class Phrase : public QObject, public IDisplayable {
    Q_OBJECT
private:
    static const char* displayTemplate() {
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
        return "%1 = \\relative %2 {\n%3\n}";
    }
public:
    enum PreviewFlag {
        Recent  = 0x1,          // is preview up to date?
        Error   = 0x2,          // generating preview resulted in error
        Loading = 0x4           // loading preview
    };
    Q_DECLARE_FLAGS(PreviewFlags,PreviewFlag)

    Phrase(QString,QString = "",Voice* = 0);
    Phrase(const Phrase&);
    ~Phrase();

public slots:
    void refresh();

    void setName   (const QString);
    void setContent(const QString);
    void setStderr (const QString);
    void setFlag   (const PreviewFlag);
    void setImage  (QImage*);

public:
    const QString name() const;
    const QString content() const;
    const QString stderr() const;
    const QImage* image();
          QSize   size();

    bool testFlag(PreviewFlag);
    void unsetFlag(PreviewFlag);
    void clearFlags();

    QString getDisplayLy() const;
    QString getWriteLy() const;

signals:
    void stderrChanged();
    void pixmapChanged();

private:
    QString      m_name;          // the name of this phrase
    Content      m_content;       // the musical content
    QString      m_stderr;        // lilypond output
    bool         m_relative_flag; // notes are relative or absolute
    QString      m_relative_note; // relative note [a-g](is|es)('*|,*)
    PreviewFlags m_preview_flags; // state of the preview
    QImage*      m_image;         // preview image of the phrase
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Phrase::PreviewFlags)

#endif // PHRASE_H
