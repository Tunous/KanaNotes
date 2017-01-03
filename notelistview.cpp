#include "notelistview.h"
#include "ui_notelistview.h"

NoteListView::NoteListView(NoteList *list, QWidget *parent) :
    QWidget(parent),
    list(list),
    ui(new Ui::NoteListView)
{
    ui->setupUi(this);
    ui->nameInput->setText(list->getName());

    foreach (Note note, list->getNotes()) {
        QTextEdit *noteInput = new QTextEdit(note.getTitle());
        ui->noteContainer->layout()->addWidget(noteInput);
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
    ui->noteContainer->layout()->addWidget(new QTextEdit());
}

void NoteListView::on_actionsButton_clicked()
{
    createNote();
}

void NoteListView::on_actionRemoveList_triggered()
{
    close();
}
