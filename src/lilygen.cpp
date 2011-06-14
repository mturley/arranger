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
void LilyGen::refreshPreview(IDisplayable* displayable) {

    Inst()->m_queue.enqueue(Job(displayable));

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
            qDebug() << "\tNo more jobs";
            continue;
        }

        // jobs need doing! get started.
        Job job = m_queue.head();
        m_queue.removeFirst();

        processJob(job);

        qDebug() << "\tUnlocking 1";
        m_sem_main.release();
    }
}

bool LilyGen::processJob(Job& job) {
    QString id = QString::number(job.m_id);
    qDebug() << "Getting next job...\t" << id;

    if(!createLyFile(job) || !createPngFile(job,80))
        qDebug() << "\tAn error occurred!";

    job.m_displayable->setImage(loadPngFile(job));

    qDebug() << "\tRemoving\t" << id + ".ly"  << QFile(id+".ly").remove();
    qDebug() << "\tRemoving\t" << id + ".png" << QFile(id+".png").remove();

    return true;
}

bool LilyGen::createLyFile(Job& job, bool display) {
    QString id = QString::number(job.m_id);
    QString filename = id + ".ly";
    qDebug() << "\tCreating\t" << filename;

    QDir::setCurrent(QDir::currentPath().append("/images"));
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "\t\tUnable to create file!";
        return false;
    }

    QTextStream out(&file);
    if(display)
        out << job.m_displayable->getDisplayLy();
    else
        out << job.m_displayable->getWriteLy();

    file.close();

    return true;
}

// create a png file from a previously generated lilypond file
bool LilyGen::createPngFile(Job& job, int resolution) {
    QString id = QString::number(job.m_id);
    QString filename = id + ".ly";
    qDebug() << "\tCreating\t" << id + ".png";

    QStringList args;
    args << "-r " + QString::number(resolution) << filename << id;

    m_proc->start("./fragment-gen.py",args);

    if(!(m_proc->waitForStarted(1000))) {
        qDebug() << "\t\tTimeout: process failed to start!";
        return false;
    }
    if(!(m_proc->waitForFinished(-1))) {
        qDebug() << "\t\tTimeout: process failed to finish!";
        return false;
    }
    if(m_proc->exitCode()) {
        qDebug() << "\t\tBad exit code!";
        return false;
    }

    return true;
}

// load a previously created png file and update the phrase
QImage* LilyGen::loadPngFile(Job& job) {
    QString id = QString::number(job.m_id);
    QString filename = id + ".png";
    qDebug() << "\tLoading \t" << filename;

    QImage* image = new QImage();
    if(!image->load(filename))
        qDebug() << "\t\tLoad failed!";

    return image;
}
