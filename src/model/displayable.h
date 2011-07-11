#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

#include <QObject>

class QImage;
class QSize;
class Phrase;

namespace PreviewFlags {
    enum PreviewFlag {
        Recent  = 0x1,          // is preview up to date?
        Error   = 0x2,          // generating preview resulted in error
        Loading = 0x4           // loading preview
    };
}

class Displayable : public QObject {
    Q_OBJECT
public:
    Displayable();
    Displayable(const Displayable&);
    ~Displayable();

public:
    bool testFlag(PreviewFlags::PreviewFlag) const;
    const QString content() const;
    const QImage* image() const;
          QSize size() const;
    void setContent(QString);
    void setImage(QImage*);

    virtual QString getDisplayLy() const = 0;
    virtual QString getWriteLy() const = 0;

    virtual QList<Phrase*>& getPhraseList() = 0;

private:
    void setFlag(PreviewFlags::PreviewFlag);
    void clearFlag(PreviewFlags::PreviewFlag);
    void clearFlags();

public slots:
    void refresh();

signals:
    void previewChanged();

private:
    uint    m_preview_flags;
    QImage* m_image;
    QString m_content;
};

#endif // IDISPLAYABLE_H
