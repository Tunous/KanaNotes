#include "notelistview.h"
#include "ui_notelistview.h"

NoteListView::NoteListView(QString name, QList<QString> *notes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteListView),
    edited(false)
{
    ui->setupUi(this);
    ui->nameInput->setText(name);

    if (notes != NULL) {
        for (int i = 0; i < notes->count(); i++) {
            Note *note = new Note(notes->at(i));
            ui->noteContainer->layout()->addWidget(note);
        }
    }

    QMenu *menu = new QMenu();
    menu->addAction(ui->actionRemoveList);

    ui->actionsButton->setMenu(menu);
}

NoteListView::~NoteListView()
{
    delete ui;
}

void NoteListView::createNote()
{
    ui->noteContainer->layout()->addWidget(new Note());
}

void NoteListView::on_actionsButton_clicked()
{
    createNote();
}

void NoteListView::on_actionRemoveList_triggered()
{
    close();
}

bool NoteListView::hasUnsavedChanges()
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

Note* NoteListView::getNote(int index) const
{
    return dynamic_cast<Note*>(ui->noteContainer->layout()->itemAt(index)->widget());
}

QString NoteListView::getName()
{
    return ui->nameInput->text();
}

QList<QString> NoteListView::getNotes()
{
    QList<QString> notes;

    for (int i = 0; i < ui->noteContainer->layout()->count(); i++) {
        Note *note = getNote(i);
        notes.append(note->getText());
    }

    return notes;
}
