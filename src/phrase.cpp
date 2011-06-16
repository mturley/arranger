#include "phrase.h"

#include <QDebug>
#include <QPixmap>

#include "voice.h"
#include "lilygen.h"

Phrase::Phrase(QString name,
               QString content,
               Voice* parent)
    : QObject(parent),
      m_name(name),
      m_content(content),
      m_image(0),
      m_preview_flags(0) { }

Phrase::Phrase(const Phrase& phrase)
    : QObject(0),
      m_name(phrase.name()),
      m_content(phrase.content()),
      m_image(0),
      m_preview_flags(0) {
}

Phrase::~Phrase() { }

/* Requests that the Image of this phrase be updated. If
 * the Recent flag is set, calling refresh will have no
 * effect.
 *
 *
 *
 */
void Phrase::refresh() {
    if(testFlag(PreviewFlags::Recent))
        return;

    clearFlags();
    setFlag(PreviewFlags::Loading);

    LilyGen::refreshPreview(this);
}

const QString Phrase::name() const {
    return m_name;
}

const QString Phrase::content() const {
    return m_content.getDisplayLy();
}

const QString Phrase::stderr() const {
    return m_stderr;
}

const QImage* Phrase::image() {
    if(!m_image)
        return new QImage();
    return m_image;
}

QSize Phrase::size() {
    if(!m_image)
        return QSize(100,20);
    return m_image->size();
}

void Phrase::setName(const QString name) {
    m_name = name;
}

void Phrase::setContent(const QString content) {
    m_content.setContent(content);
    unsetFlag(PreviewFlags::Recent);
}

void Phrase::setStderr(QString stderr) {
    m_stderr = stderr;
}

void Phrase::setFlag(PreviewFlags::PreviewFlag flag) {
    m_preview_flags |= (uint)flag;
}

bool Phrase::testFlag(PreviewFlags::PreviewFlag flag) {
    return m_preview_flags & flag != 0x0;
}

void Phrase::unsetFlag(PreviewFlags::PreviewFlag flag) {
    m_preview_flags &= ~(uint)flag;
}

void Phrase::clearFlags() {
    m_preview_flags &= 0x0;
}

void Phrase::setImage(QImage* image) {    
    clearFlags();
    setFlag(PreviewFlags::Recent);

    if(image->isNull())
        setFlag(PreviewFlags::Error);

    if(m_image)
        delete m_image;

    m_image = image;

    emit pixmapChanged();
}

QString Phrase::getDisplayLy() const {
    return QString(displayTemplate()).arg(m_relative_note,m_content.getDisplayLy());
}

QString Phrase::getWriteLy() const {
    return QString(writeTemplate()).arg(m_name,m_relative_note,m_content.getWriteLy());
}
