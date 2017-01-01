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
    QWidget *notesContainer = new QWidget();
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
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(addNoteButton, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(addNoteButton, notesContainer);

    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(addNote(QWidget*)));

    actionsButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(actionsButton, SIGNAL(clicked()), this, SLOT(showActions()));
}

void NotesList::showActions()
{
    QMenu menu;

    QAction *removeListAction = new QAction("Remove");
    menu.addAction(removeListAction);

    connect(removeListAction, SIGNAL(triggered()), this, SLOT(deleteLater()));

    menu.exec(QCursor::pos());
}

void NotesList::addNote(QWidget *widget)
{
    qDebug() << "Adding note";
    widget->layout()->addWidget(new QTextEdit());
}
