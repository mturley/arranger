#ifndef PHRASE_H
#define PHRASE_H

#include <QImage>
#include <QPixmap>

class Phrase : public QObject {
    Q_OBJECT
public:
    enum PreviewFlag {
        Recent  = 0x1,          // is preview up to date?
        Error   = 0x2,          // generating preview resulted in error
        Loading = 0x4           // loading preview
    };
    Q_DECLARE_FLAGS(PreviewFlags,PreviewFlag)

    Phrase(QString,QString = "",QObject* = 0);
    ~Phrase();
public slots:
    void refresh();

    const QString  name();
    const QString  content();
    const QString  stderr();
          QPixmap* pixmap();

    void setName   (const QString);
    void setContent(const QString);
    void setStderr (const QString);
    void setFlag   (const PreviewFlag);
    void setImage  (QImage*);

    bool testFlag(PreviewFlag);
    void unsetFlag(PreviewFlag);
    void clearFlags();

    QString getDisplayLy();
signals:
    void stderrChanged();
    void pixmapChanged();

private:
    QString      m_name;          // the name of this phrase
    QString      m_content;       // the musical content
    QString      m_stderr;        // lilypond output
    bool         m_relative_flag; // notes are relative or absolute
    QString      m_relative_note; // relative note [a-g](is|es)('*|,*)
    PreviewFlags m_preview_flags; // state of the preview
    QPixmap*     m_pixmap;
    QImage* volatile      m_image;         // preview image of the phrase
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Phrase::PreviewFlags)

#endif // PHRASE_H
