#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showListActions()
{
    QMenu menu;
    menu.addAction("Remove list");

    QAction *selectedItem = menu.exec(QCursor::pos());
    if (selectedItem) {
        qDebug() << "Selected";
    } else {
        qDebug() << "Ignored";
    };
}

void MainWindow::addList()
{
    // Header row
    QWidget *titleRow = new QWidget();
    QHBoxLayout *titleRowLayout = new QHBoxLayout(titleRow);
    titleRowLayout->setMargin(0);

    // The name of the list
    QLineEdit *listNameInput = new QLineEdit();

    // List actios button
    listActionsButton = new QToolButton();
    listActionsButton->setText("...");

    titleRowLayout->addWidget(listNameInput);
    titleRowLayout->addWidget(listActionsButton);


    // Notes container
    QWidget *notesContainer = new QWidget();
    QVBoxLayout *notesContainerLayout = new QVBoxLayout(notesContainer);
    notesContainerLayout->setMargin(0);


    // Notes area
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(notesContainer);


    // Add note button
    QPushButton *addNoteButton = new QPushButton();
    addNoteButton->setText("Add a note...");


    // The list layout
    QWidget *list = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(list);
    listLayout->setMargin(0);
    listLayout->addWidget(titleRow);
    listLayout->addWidget(scrollArea);
    listLayout->addWidget(addNoteButton);

    list->setMinimumWidth(250);
    list->setMaximumWidth(250);


    // Append before new list button
    QLayout *listContainerLayout = ui->listContainer->layout();
    QLayoutItem *lastItem = listContainerLayout->takeAt(listContainerLayout->count() - 1);

    listContainerLayout->addWidget(list);
    listContainerLayout->addItem(lastItem);


    // Connect signals
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(addNoteButton, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(addNoteButton, notesContainer);

    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(addNote(QWidget*)));

    listActionsButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listActionsButton, SIGNAL(clicked()), this, SLOT(showListActions()));
}

void MainWindow::addNote(QWidget *widget)
{
    qDebug() << "Adding note";
    widget->layout()->addWidget(new QTextEdit());
}
