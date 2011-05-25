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

    const QString getName();
    const QString getContent();
    QPixmap* getPreviewPixmap();

    void setContent(QString);
    void setLOutput(QString);
    void setFlag(PreviewFlag);
    bool testFlag(PreviewFlag);
    void clearFlags();

    void setPreview(QImage*);
signals:
    void loutputChanged();

private:
    QString      m_name;             // the name of this phrase
    QString      m_content;          // the musical content
    QString      m_loutput;          // lilypond output
    bool         m_relative_flag;    // notes are relative or absolute
    QString      m_relative_note;    // relative note [a-g](is|es)('*|,*)
    PreviewFlags m_preview_flags;    // state of the preview
    QImage*      m_preview;          // preview image of the phrase
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Phrase::PreviewFlags)

#endif // PHRASE_H
