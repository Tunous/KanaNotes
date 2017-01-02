#ifndef NOTELIST_H
#define NOTELIST_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTextEdit>

namespace Ui {
class NoteList;
}

class NoteList : public QWidget
{
    Q_OBJECT

public:
    explicit NoteList(QWidget *parent = 0);
    ~NoteList();

public slots:
    void addNote();
    void showActions();

private:
    Ui::NoteList *ui;
};

#endif // NOTELIST_H
