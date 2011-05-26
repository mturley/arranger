#ifndef LILYGEN_H
#define LILYGEN_H

#include <QDebug>
#include <QQueue>
#include <QString>
#include <QImage>
#include <QProcess>
#include <QThread>
#include <QSemaphore>
#include <cstdlib>

#include "phrase.h"

class LilyGen : public QThread {
    Q_OBJECT
private:
    struct LilyJob {
        LilyJob(Phrase* a_phrase)
            : m_id(rand()),
              m_phrase(a_phrase) { }

        int m_id;
        Phrase* m_phrase;
    };

public:
    static void refreshPreview(Phrase*);

private:
    static LilyGen* Inst();
    LilyGen();

    void enqueueJob(LilyJob);
    QString genFileContent(QString);

private:
    void run();
    bool processPhraseJob(LilyJob&);
    bool createPhraseLy(QString,Phrase*);
    bool createPng(QString,int);
    bool loadPng(QString,Phrase*);


private:
    static LilyGen* m_instance;
    QSemaphore m_sem_main;

    QQueue<LilyJob> m_queue;
    QProcess* m_proc;
};

#endif // LILYGEN_H
