#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

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
    void addNote(QWidget *scrollArea);
    void showListActions();

private:
    Ui::MainWindow *ui;
    QToolButton *listActionsButton;
};

#endif // MAINWINDOW_H
