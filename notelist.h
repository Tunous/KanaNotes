#ifndef NOTELIST_H
#define NOTELIST_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTextEdit>

#include "list.h"

namespace Ui {
class NoteList;
}

class NoteList : public QWidget
{
    Q_OBJECT

public:
    explicit NoteList(QWidget *parent = 0);
    ~NoteList();

    List *list;
    void setList(List *list);

public slots:
    void addNote();
    void showActions();

private:
    Ui::NoteList *ui;
};

#endif // NOTELIST_H
