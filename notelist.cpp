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
            note->markAsSaved();
        }
    }
}

void NoteList::addNote(Note *note)
{
    connect(note, SIGNAL(removeRequested(Note*)), this, SLOT(removeNote(Note*)));
    ui->noteContainer->layout()->addWidget(note);

    edited = true;
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

void NoteList::removeNote(Note *note)
{
    note->deleteLater();
    edited = true;
}

void NoteList::on_addNoteButton_clicked()
{
    QString text = ui->newNoteInput->text().trimmed();

    if (!text.isEmpty()) {
        addNote(new Note(text));
    }

    ui->newNoteInput->clear();
}

void NoteList::on_actionRemove_triggered()
{
    emit removeRequested(this);
}

void NoteList::on_nameInput_textEdited(const QString &arg1)
{
    edited = true;
}
