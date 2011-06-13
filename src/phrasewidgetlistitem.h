#ifndef PHRASEWIDGETLISTITEM_H
#define PHRASEWIDGETLISTITEM_H

#include <QListWidgetItem>

#include "phrasewidget.h"

class PhraseWidgetListItem : public QObject, public QListWidgetItem {
    Q_OBJECT
public:
    explicit PhraseWidgetListItem(Phrase*,QListWidget* parent);
signals:
    void changed(QListWidgetItem*);
private slots:
    void pixmapChanged();
private:
    PhraseWidget* m_phraseWidget;
};

#endif // PHRASEWIDGETLISTITEM_H
