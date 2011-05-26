#include "phrase.h"
#include "lilygen.h"
#include <QDebug>

Phrase::Phrase(QString a_name,
               QString a_content,
               Voice* parent) :
    QObject(parent),
    m_name(a_name),
    m_content(a_content),
    m_pixmap(0),
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
    return m_content;
}

const QString Phrase::stderr() {
    return m_stderr;
}

QPixmap* Phrase::pixmap() {
    QPixmap* pixmap = new QPixmap();
    if(pixmap->convertFromImage(*m_image))
        return pixmap;
    return new QPixmap();
}

void Phrase::setName(const QString name) {
    m_name = name;
}

void Phrase::setContent(QString a_content) {
    m_content = a_content;
    // maybe this should be an emit statement
    // but for now this'll do
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

QString Phrase::getDisplayLy() {
    return QString(displayTemplate()).arg(m_content);
}

QString Phrase::getWriteLy() {
    return QString(writeTemplate()).arg(m_name,m_relative_note,m_content);
}
