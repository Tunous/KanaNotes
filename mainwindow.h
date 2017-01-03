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

private slots:
    void closeAllBoards();
    void closeSelectedBoard();
    void createBoard();
    void openBoard();
    void saveBoard();
    void saveBoardAs();

private:
    Ui::MainWindow *ui;

    void closeBoard(int index);
};

#endif // MAINWINDOW_H
