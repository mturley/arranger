#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractItemModel>

class ProjectModel : public QAbstractItemModel {
public:
    ProjectModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
private:
    IParentItem *m_root;
};

#endif // PROJECTMODEL_H
