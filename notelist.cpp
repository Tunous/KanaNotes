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
            ui->noteContainer->layout()->addWidget(note);
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

void NoteList::createNote()
{
    ui->noteContainer->layout()->addWidget(new Note());
}

void NoteList::on_actionsButton_clicked()
{
    createNote();
}

void NoteList::on_actionRemoveList_triggered()
{
    close();
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
        notes.append(note->getText());
    }

    return notes;
}

void NoteList::on_nameInput_textChanged(const QString &arg1)
{
    edited = true;
}
