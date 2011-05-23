#include "lilygen.h"

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
    emit jobAdded();
}

void LilyGen::startJob() {
    LilyJob job = m_queue.head();
    // <create lilypond file>
    m_proc->start("lilypond",QStringList() << "-o" << job.m_name);
}

void LilyGen::finishJob() {

}
