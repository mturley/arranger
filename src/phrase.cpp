#include "phrase.h"
#include "lilygen.h"
#include <QDebug>

Phrase::Phrase(QString a_name,
               QString a_content,
               QObject* parent) :
    QObject(parent),
    m_name(a_name),
    m_content(a_content) { }
Phrase::~Phrase() {
    qDebug() << m_name;
    qDebug() << "Error flag:" << m_preview_flags.testFlag(Phrase::Error);
    qDebug() << "Output:" << m_loutput;
}

void Phrase::refresh() {
    LilyGen::refreshPreview(m_name,m_content,&m_loutput,&m_preview_flags,m_preview);
}
