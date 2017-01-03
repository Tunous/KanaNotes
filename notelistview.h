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
    explicit NoteListView(QWidget *parent = 0);
    ~NoteListView();

    NoteList *list;
    void setList(NoteList *list);

public slots:
    void addNote();
    void showActions();

private:
    Ui::NoteListView *ui;
};

#endif // NOTELISTVIEW_H
