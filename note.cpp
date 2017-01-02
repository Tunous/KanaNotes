#include "note.h"

Note::Note(QString title, QString description)
    : title(title), description(description) {
}

Note::Note(QString title) : Note(title, "") {
}

QString Note::getTitle() {
    return title;
}

QString Note::getDescription() {
    return description;
}

void Note::setTitle(QString title) {
    this->title = title;
}

void Note::setDescription(QString description) {
    this->description = description;
}
