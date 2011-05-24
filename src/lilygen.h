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
        LilyJob(const QString         a_name,
                const QString         a_content,
                QString*              a_loutput,
                Phrase::PreviewFlags* a_flags,
                QImage*               a_image) {
            m_name    = a_name;
            m_content = a_content;
            m_loutput = a_loutput;
            m_flags   = a_flags;
            m_image   = a_image;
        }
        inline void setLOutpout(QString msg) {
            *(m_loutput) = msg;
        }

        inline void setFlag(Phrase::PreviewFlag flag) {
            *(m_flags) |= flag;
        }

        inline void clearFlags() {
            *(m_flags) &= 0x0;
        }

        QString               m_name;
        QString               m_content;
        QString*              m_loutput;
        Phrase::PreviewFlags* m_flags;
        QImage*               m_image;
    };

public:
    static void refreshPreview(const QString,
                               const QString,
                               QString*,
                               Phrase::PreviewFlags*,
                               QImage*);

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
