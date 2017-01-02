#include "notelist.h"
#include "ui_notelist.h"

NoteList::NoteList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteList)
{
    ui->setupUi(this);

    ui->actionsButton->setContextMenuPolicy(Qt::CustomContextMenu);
}

NoteList::~NoteList()
{
    delete ui;
}

void NoteList::setList(List *list) {
    this->list = list;
    ui->nameInput->setText(list->getName());

    foreach (Note note, list->getNotes()) {
        QTextEdit *noteInput = new QTextEdit(note.getTitle());
        ui->noteContainer->layout()->addWidget(noteInput);
    }
}

void NoteList::showActions()
{
    QMenu menu;

    QAction *removeListAction = new QAction("Remove");
    connect(removeListAction, SIGNAL(triggered()), this, SLOT(deleteLater()));
    menu.addAction(removeListAction);

    menu.exec(QCursor::pos());
}

void NoteList::addNote()
{
    qDebug() << "Adding note";
    ui->noteContainer->layout()->addWidget(new QTextEdit());
}
