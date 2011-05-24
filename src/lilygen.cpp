#include "lilygen.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

LilyGen* LilyGen::m_instance = NULL;

LilyGen* LilyGen::Inst() {
    if(m_instance == NULL)
        m_instance = new LilyGen();
    return m_instance;
}

LilyGen::LilyGen(QObject* parent) :
    QObject(parent) {
    m_proc = new QProcess();
    m_proc->setWorkingDirectory("lilypond");

    connect(m_proc,SIGNAL(finished(int)),this,SLOT(finishedJob(int)));
    connect(m_proc,SIGNAL(finished(int)),this,SLOT(startJobs()));
    connect(this,SIGNAL(jobAdded()),this,SLOT(startJobs()));
}

void LilyGen::refreshPreview(QString a_name,
                             QString a_content,
                             QImage* a_image) {
    Inst()->enqueueJob(a_name,a_content,a_image);
}

void LilyGen::enqueueJob(QString a_name,
                         QString a_content,
                         QImage* a_image) {
    m_queue.enqueue(LilyJob(a_name,a_content,a_image));
    qDebug() << "Added job:" << a_name;
    emit jobAdded();
}

void LilyGen::startJobs() {
    if(m_proc->state() == (QProcess::Running || QProcess::Starting)) {
        //qDebug()
        return;
    }
    if(m_queue.count() <= 0) {
        qDebug() << "No more jobs!";
        return;
    }
    processHead();
}

void LilyGen::processHead() {
    QDir::setCurrent(QDir::currentPath().append("/images"));

    // pop head
    LilyJob job = m_queue.head();
    m_queue.removeFirst();

    qDebug() << "Starting job" << job.m_name;

    // create lilypond file
    QString filename = job.m_name + ".ly";
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to create file:" << filename;
        return;
    }
    QTextStream out(&file);
    out << genFileContent(job.m_content);
    file.close();


    // start lilypond
    QStringList args;
    args << filename << job.m_name;
    qDebug() << "Running:" << "fragment-gen.py" << args;
    m_proc->start("./fragment-gen.py",args);
}

void LilyGen::finishedJob(int e) {
    qDebug() << "Finished job." << e;
    qDebug() << m_proc->readAll();
    // <report errors if any>
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
