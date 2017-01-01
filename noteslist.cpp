#include "noteslist.h"

NotesList::NotesList(QWidget *parent) : QWidget(parent)
{
    // The name of the list
    nameInput = new QLineEdit();

    // List actios button
    actionsButton = new QToolButton();
    actionsButton->setText("...");

    // Header row
    titleRow = new QWidget();
    QHBoxLayout *titleRowLayout = new QHBoxLayout(titleRow);
    titleRowLayout->setMargin(0);
    titleRowLayout->addWidget(nameInput);
    titleRowLayout->addWidget(actionsButton);


    // Notes container
    notesContainer = new QWidget();
    QVBoxLayout *notesContainerLayout = new QVBoxLayout(notesContainer);
    notesContainerLayout->setMargin(0);


    // Notes area
    scrollArea = new QScrollArea();
    scrollArea->setWidget(notesContainer);


    // Add note button
    addNoteButton = new QPushButton();
    addNoteButton->setText("Add a note...");


    // The list layout
    QVBoxLayout *listLayout = new QVBoxLayout(this);
    listLayout->setMargin(0);
    listLayout->addWidget(titleRow);
    listLayout->addWidget(scrollArea);
    listLayout->addWidget(addNoteButton);

    setMinimumWidth(250);
    setMaximumWidth(250);

    // Connect signals
    connect(addNoteButton, SIGNAL(clicked()), this, SLOT(addNote()));

    actionsButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(actionsButton, SIGNAL(clicked()), this, SLOT(showActions()));
}

void NotesList::showActions()
{
    QMenu menu;

    QAction *removeListAction = new QAction("Remove");
    connect(removeListAction, SIGNAL(triggered()), this, SLOT(deleteLater()));
    menu.addAction(removeListAction);

    menu.exec(QCursor::pos());
}

void NotesList::addNote()
{
    qDebug() << "Adding note";
    notesContainer->layout()->addWidget(new QTextEdit());
}
