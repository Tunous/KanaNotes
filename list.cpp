#include "list.h"

List::List(QString name) : name(name) {
}

void List::addNote(const Note &note) {
    notes.append(note);
}

QString List::getName() {
    return name;
}

void List::setName(QString name) {
    this->name = name;
}

const QList<Note> List::getNotes() {
    return notes;
}
