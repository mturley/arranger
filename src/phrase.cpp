#include "phrase.h"

#include <QDebug>
#include <QPixmap>

#include "voice.h"
#include "lilygen.h"

Phrase::Phrase(QString name,
               QString content,
               Voice* parent) :
    QObject(parent),
    m_name(name),
    m_content(content),
    m_image(0) { }

Phrase::~Phrase() { }

/* Requests that the Image of this phrase be updated. If
 * the Recent flag is set, calling refresh will have no
 * effect.
 *
 *
 *
 */
void Phrase::refresh() {
    if(testFlag(Recent))
        return;

    clearFlags();
    setFlag(Loading);

    LilyGen::refreshPreview(this);
}

const QString Phrase::name() {
    return m_name;
}

const QString Phrase::content() {
    return m_content.getDisplayLy();
}

const QString Phrase::stderr() {
    return m_stderr;
}

const QImage* Phrase::image() {
    qDebug() << "Returning QImage* for" << m_name << ":" << m_image;
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
    m_preview_flags &= ~Recent;
}

void Phrase::setStderr(QString stderr) {
    m_stderr = stderr;
}

void Phrase::setFlag(Phrase::PreviewFlag flag) {
    m_preview_flags |= flag;
}

bool Phrase::testFlag(PreviewFlag flag) {
    return m_preview_flags.testFlag(flag);
}

void Phrase::unsetFlag(PreviewFlag flag) {
    m_preview_flags &= ~flag;
}

void Phrase::clearFlags() {
    m_preview_flags &= 0x0;
}

void Phrase::setImage(QImage* image) {
    clearFlags();
    setFlag(Recent);
    if(image->isNull())
        setFlag(Error);

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
