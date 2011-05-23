#ifndef PHRASE_H
#define PHRASE_H

#include <QImage>

class Phrase {
public:
    Phrase() : m_loading(false) { }
public slots:
    void refresh();

private:
    QString m_name;
    QString m_content;
    QImage* m_preview;
    bool    m_loading;
};

#endif // PHRASE_H
