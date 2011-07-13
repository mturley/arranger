#include "phrase.h"

#include <QDebug>
#include <QPixmap>

#include "voice.h"
#include "../lilygen.h"

Phrase::Phrase(QString name, QString content, Voice* parent)
    : Displayable(name) {
    setContent(content);
}

Phrase::Phrase(const Phrase& phrase)
    : Displayable(phrase) { }

Phrase::~Phrase() { }

const QString Phrase::stderr() const {
    return m_stderr;
}

void Phrase::setStderr(QString stderr) {
    m_stderr = stderr;
}

QString Phrase::getDisplayLy() const {
    return QString(displayTemplate()).arg(m_relative_note,content());
}

QString Phrase::getWriteLy() const {
    return QString(writeTemplate()).arg(name(),content());
}

QList<Phrase*>& Phrase::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    list->append(this);
    return *list;
}
