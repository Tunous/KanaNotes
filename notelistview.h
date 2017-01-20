#ifndef NOTELISTVIEW_H
#define NOTELISTVIEW_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTextEdit>

#include "note.h"

namespace Ui {
class NoteListView;
}

class NoteListView : public QWidget
{
    Q_OBJECT

public:
    explicit NoteListView(QString name, QList<QString> *notes = NULL, QWidget *parent = 0);
    ~NoteListView();

    bool hasUnsavedChanges();
    QString getName();
    QList<QString> getNotes();

private slots:
    void on_actionsButton_clicked();
    void on_actionRemoveList_triggered();

private:
    Ui::NoteListView *ui;
    bool edited;

    void createNote();
    Note* getNote(int index) const;
};

#endif // NOTELISTVIEW_H
