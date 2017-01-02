#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "notelist.h"
#include "list.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addList();
    void addList(List &listt);

private:
    Ui::MainWindow *ui;
    QList<List> lists;
};

#endif // MAINWINDOW_H
