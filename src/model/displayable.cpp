#include "displayable.h"

#include <QDebug>
#include <QImage>

#include "../lilygen.h"

Displayable::Displayable()
    : m_preview_flags(0),
      m_image(0),
      m_content(),
      m_name() { }

Displayable::Displayable(QString name)
    : m_preview_flags(0),
      m_image(0),
      m_content(),
      m_name(name) { }

Displayable::Displayable(const Displayable& displayable)
    : m_preview_flags(0),
      m_image(0),
      m_content(displayable.content()),
      m_name(displayable.name()) { }

Displayable::~Displayable() {
    if(m_image)
        delete m_image;
}

bool Displayable::testFlag(PreviewFlags::PreviewFlag flag) const {
    return (m_preview_flags & flag) != 0x0;
}
void Displayable::setFlag(PreviewFlags::PreviewFlag flag) {
    m_preview_flags |= flag;
}
void Displayable::clearFlag(PreviewFlags::PreviewFlag flag) {
    m_preview_flags &= ~flag;
}
void Displayable::clearFlags() {
    m_preview_flags &= 0x0;
}

const QString Displayable::content() const {
    return m_content;
}
const QString Displayable::name() const {
    return m_name;
}
const QImage* Displayable::image() const {
    return m_image;
}
QSize Displayable::size() const {
    return m_image->size();
}

void Displayable::setContent(QString content) {
    m_content = content;
    clearFlag(PreviewFlags::Recent);
}
void Displayable::setName(QString name) {
    m_name = name;
}

void Displayable::setImage(QImage* image) {
    clearFlags();
    setFlag(PreviewFlags::Recent);

    if(image->isNull())
        setFlag(PreviewFlags::Error);

    if(m_image)
        delete m_image;

    m_image = image;

    emit previewChanged();
}

void Displayable::refresh() {
    if(testFlag(PreviewFlags::Recent))
        return;

    clearFlags();
    setFlag(PreviewFlags::Loading);

    LilyGen::refreshPreview(this);
}
