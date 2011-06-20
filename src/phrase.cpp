#include "phrase.h"

#include <QDebug>
#include <QPixmap>

#include "voice.h"
#include "lilygen.h"

Phrase::Phrase(QString name, QString content, Voice* parent)
    : m_name(name) {
    setContent(content);
}

Phrase::Phrase(const Phrase& phrase)
    : Displayable(phrase),
      m_name(phrase.name()) { }

Phrase::~Phrase() { }

const QString Phrase::name() const {
    return m_name;
}

const QString Phrase::stderr() const {
    return m_stderr;
}

void Phrase::setName(const QString name) {
    m_name = name;
}

void Phrase::setStderr(QString stderr) {
    m_stderr = stderr;
}

QString Phrase::getDisplayLy() const {
    return QString(displayTemplate()).arg(m_relative_note,content());
}

QString Phrase::getWriteLy() const {
    return QString(writeTemplate()).arg(m_name,m_relative_note,content());
}
