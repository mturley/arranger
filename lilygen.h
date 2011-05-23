#ifndef LILYGEN_H
#define LILYGEN_H

#include <QQueue>
#include <QString>
#include <QImage>
#include <QProcess>

#include "phrase.h"

class LilyGen : public QObject {
    Q_OBJECT
private:
    struct LilyJob {
        LilyJob(QString a_name,
                QString a_content,
                QImage* a_image) :
            m_name(a_name),
            m_content(a_content),
            m_image(a_image) { }

        QString m_name;
        QString m_content;
        QImage* m_image;
    };

public:
    static void refreshPreview(QString,QString,QImage*);

private:
    LilyGen(QObject* parent = 0);
    static LilyGen* Inst();

    void enqueueJob(QString,QString,QImage*);

signals:
    void jobAdded();

private slots:
    void startJob();
    void finishJob();

private:
    static LilyGen* m_instance;
    QQueue<LilyJob> m_queue;
    QProcess* m_proc;
};

#endif // LILYGEN_H
