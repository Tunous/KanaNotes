#include "notelist.h"
#include "ui_notelist.h"

NoteList::NoteList(QString name, QList<QString> *notes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteList)
{
    ui->setupUi(this);
    ui->nameInput->setText(name);
    ui->noteContainer->layout()->setAlignment(Qt::AlignTop);

    if (notes != NULL) {
        for (int i = 0; i < notes->count(); i++) {
            Note *note = new Note(notes->at(i));
            addNote(note);
        }
    }

    QMenu *menu = new QMenu();
    menu->addAction(ui->actionRemove);
    menu->addAction(ui->actionMoveLeft);
    menu->addAction(ui->actionMoveRight);

    ui->actionsButton->setMenu(menu);

    markAsSaved();
}

NoteList::~NoteList()
{
    delete ui;
}

void NoteList::markAsSaved()
{
    edited = false;

    for (int i = 0; i < ui->noteContainer->layout()->count(); i++) {
        getNote(i)->markAsSaved();
    }
}

void NoteList::addNote(Note *note)
{
    connect(note, SIGNAL(removeRequested(Note*)), this, SLOT(destroyNote(Note*)));
    connect(note, SIGNAL(moveRequested(Note*)), this, SLOT(requestMoveNote(Note*)));
    connect(note, SIGNAL(moveInDirectionRequested(Note*,int)), this, SLOT(requestMoveNoteInDirection(Note*,int)));

    ui->noteContainer->layout()->addWidget(note);

    edited = true;
}

void NoteList::requestMoveNote(Note *note)
{
    emit moveNoteRequested(this, note);
}

void NoteList::requestMoveNoteInDirection(Note *note, int direction)
{
    emit moveNoteInDirectionRequested(this, note, direction);
}

bool NoteList::hasUnsavedChanges()
{
    if (edited) {
        return true;
    }

    int count = ui->noteContainer->layout()->count();
    for (int i = 0; i < count; i++) {
        if (getNote(i)->hasUnsavedChanges()) {
            return true;
        }
    }

    return false;
}

Note* NoteList::getNote(int index) const
{
    return dynamic_cast<Note*>(ui->noteContainer->layout()->itemAt(index)->widget());
}

QString NoteList::getName()
{
    return ui->nameInput->text();
}

QList<QString> NoteList::getNotes()
{
    QList<QString> notes;

    for (int i = 0; i < ui->noteContainer->layout()->count(); i++) {
        notes.append(getNote(i)->getText());
    }

    return notes;
}

void NoteList::destroyNote(Note *note)
{
    note->deleteLater();
    edited = true;
}

void NoteList::removeNote(Note *note)
{
    ui->noteContainer->layout()->removeWidget(note);
    note->disconnect();
    edited = true;
}

void NoteList::addNewNote()
{
    QString text = ui->newNoteInput->text().trimmed();

    if (!text.isEmpty()) {
        addNote(new Note(text));
    }

    ui->newNoteInput->clear();
}

void NoteList::on_addNoteButton_clicked()
{
    addNewNote();
}

void NoteList::on_actionRemove_triggered()
{
    emit removeRequested(this);
}

void NoteList::on_nameInput_textEdited(const QString &arg1)
{
    edited = true;
}

void NoteList::on_newNoteInput_returnPressed()
{
    addNewNote();
}

void NoteList::on_actionMoveRight_triggered()
{
    emit moveInDirectionRequested(this, 1);
}

void NoteList::on_actionMoveLeft_triggered()
{
    emit moveInDirectionRequested(this, -1);
}
