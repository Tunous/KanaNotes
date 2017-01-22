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
    void addNote(Note *note);

public slots:
    void removeNote(Note *note);

signals:
    void removeRequested(NoteList *list);
    void noteMoveRequested(NoteList *list, Note *note);

private slots:
    void on_addNoteButton_clicked();
    void on_actionRemove_triggered();
    void on_nameInput_textEdited(const QString &arg1);

    void on_newNoteInput_returnPressed();

    void requestMoveNote(Note *note);
    void destroyNote(Note *note);

private:
    Ui::NoteList *ui;
    bool edited;

    Note* getNote(int index) const;
    void addNewNote();
};

#endif // NOTELIST_H
