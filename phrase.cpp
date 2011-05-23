#include "phrase.h"
#include "lilygen.h"

void Phrase::refresh() {
    LilyGen::refreshPreview(m_name,m_content,m_preview);
}
