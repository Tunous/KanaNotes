#ifndef NOTELIST_H
#define NOTELIST_H

#include <QList>
#include "note.h"

class NoteList
{
public:
    NoteList(QString name);

    void addNote(const Note &note);

    QString getName();
    void setName(QString name);

    const QList<Note> getNotes();

private:
    QString name;
    QList<Note> notes;
};

#endif // NOTELIST_H
