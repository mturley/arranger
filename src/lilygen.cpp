#include "lilygen.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QProcess>

#include "phrase.h"

LilyGen* LilyGen::m_instance = NULL;

LilyGen* LilyGen::Inst() {
    if(m_instance == NULL)
        m_instance = new LilyGen();
    return m_instance;
}

LilyGen::LilyGen() {
    start();
}

// static refreshPreview
// returns exit code, stores output in loutput, modifies flags, stores image in a_image
void LilyGen::refreshPreview(Phrase* a_phrase) {

    Inst()->m_queue.enqueue(LilyJob(a_phrase));
    //qDebug() << "unlock from add";
    if(Inst()->m_sem_main.available() == 0)
        Inst()->m_sem_main.release();
}

// using a semaphore instead of a mutex since QMutex keeps track of which
// thread locked it, which isn't what I want. don't freak out about the goto's,
// they're there to make this easier to read, not more complicated.
void LilyGen::run() {
    // have to initialize in thread to avoid family issues
    m_proc = new QProcess();
    while(true) {
        qDebug() << "Locking" << m_sem_main.available();

        // try to acquire all available resources
        if(m_sem_main.available() > 0)
            m_sem_main.acquire(m_sem_main.available());
        else
            m_sem_main.acquire();

        // make sure there's something left to do
        if(m_queue.count() <= 0) {
            qDebug() << "    No more jobs";
            continue;
        }

        // jobs need doing! get started.
        LilyJob job = m_queue.head();
        m_queue.removeFirst();
        processPhraseJob(job);

        qDebug() << "    Unlocking";
        m_sem_main.release();
    }
}

bool LilyGen::processPhraseJob(LilyJob& job) {
    qDebug() << "Getting next job..." << job.m_phrase->name();
    QString id;
    id += QString::number(job.m_id);

    if(job.m_phrase->testFlag(Phrase::Recent)) {
        qDebug() << "    Job already done";
        return false;
    }

    job.m_phrase->clearFlags();
    job.m_phrase->setFlag(Phrase::Loading);

    if(!createPhraseLy(id,job.m_phrase))
        goto error;

    if(!createPng(id,100))
        goto error;

    if(!loadPng(id,job.m_phrase))
        goto error;

    goto done;

error:
    qDebug() << "    An error occurred!";
    job.m_phrase->setFlag(Phrase::Error);
done:
    qDebug() << "    Removing" << id + ".ly" << QFile(id+".ly").remove();
    qDebug() << "    Removing" << id + ".png" << QFile(id+".png").remove();
    job.m_phrase->unsetFlag(Phrase::Loading);
    job.m_phrase->setFlag(Phrase::Recent);

    return true;
}

// create a lilypond file for a Phrase
// this should probably be generalized later
bool LilyGen::createPhraseLy(const QString& id, Phrase* phrase) {
    qDebug() << "    Writing file..." << id;

    QDir::setCurrent(QDir::currentPath().append("/images"));
    QFile file(id + ".ly");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "        Unable to create file:" << id + ".ly";
        return false;
    }

    QTextStream out(&file);
    out << phrase->getDisplayLy();
    qDebug() << "    Closing file";
    file.close();

    return true;
}

// create a png file from a previously generated lilypond file
bool LilyGen::createPng(const QString& id, int resolution = 100) {
    qDebug() << "    Creating png...";

    QStringList args;
    args << "-r " + QString::number(resolution)<< id + ".ly" << id;

    qDebug() << "    ./fragment-gen.py" << args;
    m_proc->start("./fragment-gen.py",args);

    if(!(m_proc->waitForStarted(1000))) {
        qDebug() << "        Timeout: process failed to start!";
        return false;
    }

    qDebug() << "    Waiting for process to finish...";
    if(!(m_proc->waitForFinished(-1))) {
        qDebug() << "        Timeout: process failed to finish!";
        return false;
    }

    if(m_proc->exitCode())
        return false;

    return true;
}

// load a previously created png file and update the phrase
bool LilyGen::loadPng(const QString& id,Phrase* phrase) {
    qDebug() << "    Loading png...";

    QImage* image = new QImage();
    if(!image->load(id + ".png")) {
        qDebug() << "        Load failed!" << id;
        return false;
    }
    qDebug() << "    Setting image.";
    phrase->setImage(image);

    return true;
}
