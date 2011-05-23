#include "phrase.h"
#include "lilygen.h"

Phrase::Phrase(QString a_name,
               QString a_content,
               QObject* parent) :
    QObject(parent),
    m_name(a_name),
    m_content(a_content),
    m_loading(false) { }

void Phrase::refresh() {
    LilyGen::refreshPreview(m_name,m_content,m_preview);
}
