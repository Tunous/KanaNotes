#ifndef NOTELIST_H
#define NOTELIST_H

#include <QWidget>
#include <QMenu>
#include <QDebug>
#include <QTextEdit>

#include "note.h"

namespace Ui {
class NoteList;
}

class NoteList : public QWidget
{
    Q_OBJECT

public:
    explicit NoteList(QString name, QList<QString> *notes = NULL, QWidget *parent = 0);
    ~NoteList();

    bool hasUnsavedChanges();
    QString getName();
    QList<QString> getNotes();
    void saved();

signals:
    void removeRequested(NoteList *list);

private slots:
    void removeNote(Note *note);

    void on_addNoteButton_clicked();
    void on_actionRemove_triggered();
    void on_nameInput_textEdited(const QString &arg1);

    void on_newNoteInput_returnPressed();

private:
    Ui::NoteList *ui;
    bool edited;

    void addNote(Note *note);
    Note* getNote(int index) const;
    void addNewNote();
};

#endif // NOTELIST_H
