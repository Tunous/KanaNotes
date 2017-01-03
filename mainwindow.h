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
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionOpenBoard_triggered();

    void on_actionNewBoard_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCloseBoard_triggered();

    void on_actionCloseAllBoards_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    void closeBoard(int index);
    void closeAllBoards();
    void closeSelectedBoard();
    void createBoard();
    void openBoard();
    void saveBoard();
    void saveBoardAs();

    void setBoardActionsEnabled(bool enabled);
    void addBoard(QString fileName);

    BoardWidget* getBoard(int index);
};

#endif // MAINWINDOW_H
