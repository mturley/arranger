#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// delete this
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void init();

private slots:
    void onTreeItemClicked(QTreeWidgetItem* item, int col);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
