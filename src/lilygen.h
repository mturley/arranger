#ifndef LILYGEN_H
#define LILYGEN_H

#include <QDebug>
#include <QQueue>
#include <QString>
#include <QImage>
#include <QProcess>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSemaphore>

#include "phrase.h"

class LilyGen : public QThread {
    Q_OBJECT
private:
    struct LilyJob {
        LilyJob(Phrase* a_phrase) : m_phrase(a_phrase) { }

        Phrase* m_phrase;
    };

public:
    static void refreshPreview(Phrase*);

private:
    static LilyGen* Inst();
    LilyGen(QObject* parent = 0);

    void enqueueJob(LilyJob);
    QString genFileContent(QString);

private:
    void run();
    bool writeFile(const QString,QString);
    bool startProc(const QString,QStringList);
    void updateJob(LilyJob&);


private:
    static LilyGen* m_instance;
    QSemaphore m_sem_main;
    QMutex m_mut_main; //
    QMutex m_mut_proc;

    QQueue<LilyJob> m_queue;
    QProcess* m_proc;
};

#endif // LILYGEN_H
