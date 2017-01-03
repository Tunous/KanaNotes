#include "notelist.h"

NoteList::NoteList(QString name) : name(name) {
}

void NoteList::addNote(const Note &note) {
    notes.append(note);
}

QString NoteList::getName() {
    return name;
}

void NoteList::setName(QString name) {
    this->name = name;
}

const QList<Note> NoteList::getNotes() {
    return notes;
}
