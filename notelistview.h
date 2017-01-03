#ifndef NOTELISTVIEW_H
#define NOTELISTVIEW_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTextEdit>

#include "notelist.h"

namespace Ui {
class NoteListView;
}

class NoteListView : public QWidget
{
    Q_OBJECT

public:
    explicit NoteListView(NoteList *list, QWidget *parent = 0);
    ~NoteListView();

    NoteList *list;

private slots:
    void on_actionsButton_triggered(QAction *action);
    void on_actionsButton_clicked();

private:
    Ui::NoteListView *ui;

    void createNote();
};

#endif // NOTELISTVIEW_H
