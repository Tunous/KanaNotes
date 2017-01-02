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
