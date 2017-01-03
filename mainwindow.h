#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "notelistview.h"
#include "boardwidget.h"
#include "notelist.h"

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
    void openBoard();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
