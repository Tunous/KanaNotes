#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "notelistview.h"
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
    void addList();
    void addList(NoteList &listt);

private:
    Ui::MainWindow *ui;
    QList<NoteList> lists;
};

#endif // MAINWINDOW_H
