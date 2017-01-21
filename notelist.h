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

    void removeNote(Note *note);

private slots:
    void on_actionsButton_clicked();
    void on_actionRemoveList_triggered();

    void on_nameInput_textChanged(const QString &arg1);
    void on_note_removeRequested(Note *note);

private:
    Ui::NoteList *ui;
    bool edited;

    void addNote(Note *note);
    Note* getNote(int index) const;
};

#endif // NOTELIST_H
