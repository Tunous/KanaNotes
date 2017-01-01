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
    NotesList *list = new NotesList();

    QLayout *listContainerLayout = ui->listContainer->layout();
    QLayoutItem *lastItem = listContainerLayout->takeAt(listContainerLayout->count() - 1);

    listContainerLayout->addWidget(list);
    listContainerLayout->addItem(lastItem);
}
