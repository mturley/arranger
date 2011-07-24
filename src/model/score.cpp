#include <QDebug>

#include "score.h"

Score::Score()
    : Displayable(),
      QTreeWidgetItem(1000) {
    this->setText(0,"Unnamed Staff");
}

Score::Score(QString name)
    : Displayable(name),
      QTreeWidgetItem(1000) {
    this->setText(0,name);
}

Score::Score(const Score& s)
    : Displayable(s),
      QTreeWidgetItem(1000) {
    qDebug() << "Staves:" << s.m_staves;
    for(int i = 0; i < s.m_staves.size(); i++)
        addStaff(new Staff(*s.m_staves.at(i)));
    this->setText(0,name());
}

Score::~Score() {
    qDebug() << "Deconstructing Score:" << name();
    for(int i = 0; i < m_staves.size(); i++) {
        qDebug() << "  Deleting Staff at" << m_staves.at(i);
        delete m_staves.at(i);
    }
}

void Score::addStaff(Staff* staff) {
    m_staves.append(staff);
    this->addChild(staff);
}

QString Score::getDisplayLy() const {
    return QString();
}

QString Score::getWriteLy() const {
    return QString();
}

QList<Phrase*>& Score::getPhraseList() {
    QList<Phrase*>* list = new QList<Phrase*>();
    for(int i = 0; i < m_staves.size(); i++)
        list->append(m_staves.at(i)->getPhraseList());
    return *list;
}

QDataStream& operator<<(QDataStream& out, const Score& score) {
    score.Displayable::operator<<(out);
    QList<Staff> list;
    for(int i = 0; i < score.m_staves.size(); i++)
        list.append(*score.m_staves.at(i));
    return out << list;
}

QDataStream& operator>>(QDataStream& in, Score& score) {
    score.Displayable::operator>>(in);
    QList<Staff> list;
    in >> list;
    qDebug() << "Reading Score Data...";
    qDebug() << "  list.size()" << list.size();
    for(int i = 0; i < list.size(); i++)
        score.addStaff(new Staff(list.at(i)));
    return in;
}
