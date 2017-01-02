#ifndef LIST_H
#define LIST_H

#include <QList>
#include "note.h"

class List
{
public:
    List(QString name);

    void addNote(const Note &note);

    QString getName();
    void setName(QString name);

    const QList<Note> getNotes();

private:
    QString name;
    QList<Note> notes;
};

#endif // LIST_H
