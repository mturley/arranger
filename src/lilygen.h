#ifndef LILYGEN_H
#define LILYGEN_H

#include <cstdlib>

#include <QQueue>
#include <QSemaphore>
#include <QString>
#include <QThread>

class QProcess;
class Phrase;

// LilyGen follows the singleton pattern but its only public functions are
// static. Use LilyGen to refresh the image of displayable objects.
//
// Right now only Phrase objects are supported.
//
// Example usage:
//
//   Phrase phrase = new Phrase(...);
//   LilyGen::refreshPreview(&phrase);
//
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

private:
    void run();

    bool processPhraseJob(LilyJob&);
    bool createPhraseLy(const QString&,Phrase*);
    bool createPng(const QString&,int);
    bool loadPng(const QString&,Phrase*);

private:
    // Singleton instance of the LilyGen class
    static LilyGen* m_instance;

    // This semaphore is used to control the
    // looping of the run() function
    QSemaphore      m_sem_main;

    // A queue of LilyJobs that need processing.
    // Add to queue with enqueueJob()
    QQueue<LilyJob> m_queue;

    // Process used in the run() loop to generate
    // png files from lilypond files
    QProcess*       m_proc;
};

#endif // LILYGEN_H
