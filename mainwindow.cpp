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

void MainWindow::addList()
{
    QLineEdit *listNameInput = new QLineEdit();
    QToolButton *listActionsButton = new QToolButton();
    listActionsButton->setText("...");

    QHBoxLayout *titleRowLayout = new QHBoxLayout();
    titleRowLayout->setMargin(0);
    titleRowLayout->addWidget(listNameInput);
    titleRowLayout->addWidget(listActionsButton);

    QWidget *titleRow = new QWidget();
    titleRow->setLayout(titleRowLayout);

    QTextEdit *note = new QTextEdit();

    QPushButton *addNoteButton = new QPushButton();
    addNoteButton->setText("Add a note...");

    QVBoxLayout *listLayout = new QVBoxLayout();
    listLayout->setMargin(0);
    listLayout->addWidget(titleRow);
    listLayout->addWidget(note);
    listLayout->addWidget(addNoteButton);

    QWidget *list = new QWidget();
    list->setMinimumWidth(250);
    list->setMaximumWidth(250);
    list->setLayout(listLayout);

    QLayout *listContainerLayout = ui->listContainer->layout();
    QLayoutItem *lastItem = listContainerLayout->takeAt(listContainerLayout->count() - 1);

    listContainerLayout->addWidget(list);
    listContainerLayout->addItem(lastItem);
}
