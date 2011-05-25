#include "phrase.h"
#include "lilygen.h"
#include <QDebug>

Phrase::Phrase(QString a_name,
               QString a_content,
               QObject* parent) :
    QObject(parent),
    m_name(a_name),
    m_content(a_content),
    m_preview(0) { }
Phrase::~Phrase() {
    qDebug() << m_name;
    qDebug() << "Error flag:" << m_preview_flags.testFlag(Phrase::Error);
    qDebug() << "Output:" << m_loutput;
}

void Phrase::refresh() {
    LilyGen::refreshPreview(this);
}

const QString Phrase::getName() {
    return m_name;
}

const QString Phrase::getContent() {
    return m_content;
}

QPixmap* Phrase::getPreviewPixmap() {
    QPixmap* pixmap = new QPixmap();
    return new QPixmap();
    if(pixmap->convertFromImage(*m_preview));
        return pixmap;
}

void Phrase::setContent(QString a_content) {
    m_content = a_content;
    // maybe this should be an emit statement
    // but for now this'll do
    m_preview_flags &= ~Recent;
}

void Phrase::setLOutput(QString msg) {
    m_loutput = msg;
}

void Phrase::setFlag(Phrase::PreviewFlag flag) {
    m_preview_flags |= flag;
}

bool Phrase::testFlag(PreviewFlag flag) {
    return m_preview_flags.testFlag(flag);
}

void Phrase::clearFlags() {
    m_preview_flags &= 0x0;
}

void Phrase::setPreview(QImage* a_preview) {
    qDebug() << m_preview;
    // save old image
    QImage* temp = m_preview;
    m_preview = a_preview;
    // delete old image if necessary
    if(temp) {
        qDebug() << "Deleting previous image.";
        delete temp;
    }
}
