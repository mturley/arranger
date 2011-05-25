#include "lilygen.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QPixmap>
#include <QImageReader>

LilyGen* LilyGen::m_instance = NULL;

LilyGen* LilyGen::Inst() {
    if(m_instance == NULL)
        m_instance = new LilyGen();
    return m_instance;
}

LilyGen::LilyGen(QObject* parent) {
    //m_sem_main.
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

        qDebug() << "    Any more jobs?";
        if(m_queue.count() <= 0)
            continue;

        qDebug() << "Getting next job...";
        // pop!
        LilyJob job = m_queue.head();
        m_queue.removeFirst();
        // needs to be here because of goto's
        QString filename = job.m_phrase->getName() + ".ly";
        qDebug() << "    " << job.m_phrase->getName();

        qDebug() << "    Is job already done?";
        if(job.m_phrase->testFlag(Phrase::Recent))
            goto done;

        qDebug() << "    Set loading flag";
        job.m_phrase->setFlag(Phrase::Loading);

        qDebug() << "    Writing file...";
        if(!writeFile(filename,genFileContent(job.m_phrase->getContent())))
            goto done;

        qDebug() << "    Starting process...";
        if(!startProc("./fragment-gen.py",QStringList() << "-r 70" << filename << job.m_phrase->getName()))
            goto done;

        updateJob(job);

        qDebug() << "    Script error?";
        if(m_proc->exitCode() != 0)
            goto done;

        // load image
        // braces to indicate scope (avoids cross initilization error)
        // ps, can't load QPixmap outside of GUI thread, so using QImage
        {
            qDebug() << "    Loading image...";
            QImage* image = new QImage();
            if(!image->load(job.m_phrase->getName() + ".png")) {
                qDebug() << "    Load failed!";
                break;
            }
            qDebug() << "    Setting image.";
            job.m_phrase->setPreview(image);
        }

        done:
        qDebug() << "    Unlocking";
        m_sem_main.release();
    }
}

bool LilyGen::writeFile(const QString filename,QString content) {
    QDir::setCurrent(QDir::currentPath().append("/images"));
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "        Unable to create file:" << filename;
        return false;
    }

    QTextStream out(&file);
    out << content;
    qDebug() << "    Closing file";
    file.close();

    return true;
}

bool LilyGen::startProc(const QString proc, QStringList args) {
    m_proc->start(proc,args);

    if(!(m_proc->waitForStarted(1000))) {
        qDebug() << "        Timeout: process failed to start!";
        return false;
    }

    qDebug() << "    Waiting for process to finish...";
    if(!(m_proc->waitForFinished(-1))) {
        qDebug() << "        Timeout: process failed to finish!";
        return false;
    }
    return true;
}

void LilyGen::updateJob(LilyJob& job) {
    qDebug() << "    Set loutput";
    job.m_phrase->setLOutput(m_proc->readAllStandardError());
    qDebug() << "    Clear flags";
    job.m_phrase->clearFlags();

    // set flags
    qDebug() << "    Set flags";
    switch(m_proc->exitCode()) {
        case  0: job.m_phrase->setFlag(Phrase::Recent); break;
        default: job.m_phrase->setFlag(Phrase::Error);  break;
    }
}

QString LilyGen::genFileContent(QString block) {
    // this function needs a lot of work
    // but this should suffice for now :/

    QString result = "\\version \"2.8.1\"\n";
    result.append(   "\\header {\n");
    result.append(   "  tagline = \"\"\n");
    result.append(   "}\n");
    result.append(   "\\paper {\n");
    result.append(   "  ragged-right = ##t\n");
    result.append(   "  indent = 0.0\\mm\n");
    result.append(   "  line-width = 100\\pt\n");
    result.append(   "}\n");

    result.append("{").append(block).append("}\n");

    return result;
}
