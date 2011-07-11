#ifndef LILYGEN_H
#define LILYGEN_H

#include <cstdlib>

#include <QImage>
#include <QQueue>
#include <QSemaphore>
#include <QString>
#include <QThread>

#include "model/displayable.h"

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
    struct Job {
        Job(Displayable* displayable)
            : m_id(rand()),
            m_displayable(displayable) { }

        int m_id;
        Displayable* m_displayable;
    };

public:
    static void refreshPreview(Displayable*);

private:
    static LilyGen* Inst();
    LilyGen();

    void enqueueJob(Job);

private:
    void run();

    bool    processJob(Job&);
    bool    createLyFile(Job&,bool = true);
    bool    createPngFile(Job&,int = 100);
    QImage* loadPngFile(Job&);

private:
    // Singleton instance of the LilyGen class
    static LilyGen* m_instance;

    // This semaphore is used to control the
    // looping of the run() function
    QSemaphore      m_sem_main;

    // A queue of Jobs that need processing.
    // Add to queue with enqueueJob()
    QQueue<Job> m_queue;

    // Process used in the run() loop to generate
    // png files from lilypond files
    QProcess*       m_proc;
};

#endif // LILYGEN_H
