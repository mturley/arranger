#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Displayable;
class QTreeWidgetItem;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    void testModel();

private slots:
    void onTreeItemClicked(QTreeWidgetItem* item, int col);
    void onContentEditChanged();
    void onNameEditChanged(QString);
    void onRefreshButtonClicked();

private:
    Ui::MainWindow *ui;
    Displayable* m_selection;

};

#endif // MAINWINDOW_H
