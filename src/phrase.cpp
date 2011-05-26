#include "phrase.h"

#include <QDebug>
#include <QPixmap>

#include "voice.h"
#include "lilygen.h"

Phrase::Phrase(QString a_name,
               QString a_content,
               Voice* parent) :
    QObject(parent),
    m_name(a_name),
    m_content(a_content),
    m_image(0) { }
Phrase::~Phrase() {
}

void Phrase::refresh() {
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

QPixmap* Phrase::pixmap() {
    QPixmap* pixmap = new QPixmap();
    if(!m_image)
        return new QPixmap();
    if(!pixmap->convertFromImage(*m_image))
        return new QPixmap();
    return pixmap;
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
    // save old image for the moment
    QImage* temp = m_image;
    m_image = image;
    // delete old image if necessary
    if(temp)
        delete temp;

    emit pixmapChanged();
}

QString Phrase::getDisplayLy() const {
    return QString(displayTemplate()).arg(m_relative_note,m_content.getDisplayLy());
}

QString Phrase::getWriteLy() const {
    return QString(writeTemplate()).arg(m_name,m_relative_note,m_content.getWriteLy());
}
