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
    menu->addAction(ui->actionRemoveList);

    ui->actionsButton->setMenu(menu);

    saved();
}

NoteList::~NoteList()
{
    delete ui;
}

void NoteList::saved()
{
    edited = false;

    for (int i = 0; i < ui->noteContainer->layout()->count(); i++) {
        Note *note = getNote(i);
        if (note != NULL) {
            note->saved();
        }
    }
}

void NoteList::addNote(Note *note)
{
    connect(note, SIGNAL(removeRequested(Note*)), this, SLOT(removeNote(Note*)));
    ui->noteContainer->layout()->addWidget(note);
}

void NoteList::on_actionsButton_clicked()
{
    emit removeRequested(this);
    //addNote(new Note());
}

void NoteList::on_actionRemoveList_triggered()
{
    emit removeRequested(this);
}

bool NoteList::hasUnsavedChanges()
{
    if (edited) {
        return true;
    }

    int count = ui->noteContainer->layout()->count();
    for (int i = 0; i < count; i++) {
        Note *note = getNote(i);
        if (note != NULL && note->hasUnsavedChanges()) {
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
        Note *note = getNote(i);
        if (note != NULL) {
            notes.append(note->getText());
        }
    }

    return notes;
}

void NoteList::on_nameInput_textChanged(const QString &arg1)
{
    edited = true;
}

void NoteList::removeNote(Note *note)
{
    ui->noteContainer->layout()->removeWidget(note);
    note->disconnect();
    delete note;
}

void NoteList::on_addNoteButton_clicked()
{
    addNote(new Note(ui->newNoteInput->text()));
    ui->newNoteInput->clear();
}
