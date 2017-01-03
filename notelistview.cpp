#include "notelistview.h"
#include "ui_notelistview.h"

NoteListView::NoteListView(NoteList *list, QWidget *parent) :
    QWidget(parent),
    list(list),
    ui(new Ui::NoteListView)
{
    ui->setupUi(this);
    ui->actionsButton->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->nameInput->setText(list->getName());

    foreach (Note note, list->getNotes()) {
        QTextEdit *noteInput = new QTextEdit(note.getTitle());
        ui->noteContainer->layout()->addWidget(noteInput);
    }
}

NoteListView::~NoteListView()
{
    delete ui;
}

void NoteListView::showActions()
{
    QMenu menu;

    QAction *removeListAction = new QAction("Remove");
    connect(removeListAction, SIGNAL(triggered()), this, SLOT(deleteLater()));
    menu.addAction(removeListAction);

    menu.exec(QCursor::pos());
}

void NoteListView::addNote()
{
    qDebug() << "Adding note";
    ui->noteContainer->layout()->addWidget(new QTextEdit());
}
