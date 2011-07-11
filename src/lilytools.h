#ifndef LILYTOOLS_H
#define LILYTOOLS_H

class QString;
class QStringList;

namespace LilyTools {
    bool isBlock(const QString&);
    bool isNote(const QString&);

    QStringList tokenize(const QString&);

    QString format(const QString&,int,int);
}

#endif // LILYTOOLS_H
