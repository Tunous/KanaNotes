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

void MainWindow::openBoard()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open board...", QDir::currentPath(), "Text files (*.txt)");
    QFileInfo fileInfo(fileName);

    BoardWidget *board = new BoardWidget(fileName);
    ui->tabWidget->addTab(board, fileInfo.fileName());
}
