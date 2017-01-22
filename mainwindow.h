#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "notelist.h"
#include "board.h"

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

    Board* getBoard(int index);
    bool canClose(Board *board);

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
