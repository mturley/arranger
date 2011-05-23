#ifndef PHRASE_H
#define PHRASE_H

#include <QImage>

class Phrase : public QObject {
    Q_OBJECT
public:
    Phrase(QString,QString = "",QObject* = 0);
public slots:
    void refresh();

private:
    QString m_name;
    QString m_content;
    QImage* m_preview;
    bool    m_loading;
};

#endif // PHRASE_H
