#include "phrasewidgetlistitem.h"

#include <QDebug>
#include <QHBoxLayout>

PhraseWidgetListItem::PhraseWidgetListItem(Phrase* phrase, QListWidget* parent)
    : QListWidgetItem(parent){
    m_phraseWidget = new PhraseWidget(phrase);

    this->setSizeHint(m_phraseWidget->sizeHint());
    this->listWidget()->setItemWidget(this,m_phraseWidget);

    connect(m_phraseWidget,SIGNAL(pixmapChanged()),this,SLOT(pixmapChanged()));
    connect(this,SIGNAL(changed(QListWidgetItem*)),this->listWidget(),SIGNAL(itemChanged(QListWidgetItem*)));
}

void PhraseWidgetListItem::pixmapChanged() {
    qDebug() << "called" << m_phraseWidget->sizeHint();
    this->setSizeHint(m_phraseWidget->sizeHint());
    emit changed(this);
}
