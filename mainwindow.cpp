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

    ui->actionSave->setEnabled(true);
    ui->actionSaveAs->setEnabled(true);
    ui->actionCloseBoard->setEnabled(true);
    ui->actionCloseAllBoards->setEnabled(true);
}

void MainWindow::closeBoard(int index)
{
    if (index < 0) {
        return;
    }

    BoardWidget *board = dynamic_cast<BoardWidget*>(ui->tabWidget->widget(index));
    if (board->hasUnsavedChanges()) {
        qDebug() << "TODO: Prompt to save";
        return;
    }

    ui->tabWidget->removeTab(index);
}

void MainWindow::closeSelectedBoard()
{
    int index = ui->tabWidget->currentIndex();
    closeBoard(index);
}

void MainWindow::closeAllBoards()
{
    // TODO: Prompt to save
    int tabsCount = ui->tabWidget->count();

    for (int i = 0; i < tabsCount; ++i) {
        ui->tabWidget->removeTab(0);
    }
}

void MainWindow::saveBoard()
{
    // TODO
}

void MainWindow::saveBoardAs()
{
    // TODO
}

void MainWindow::createBoard()
{
    // TODO
}
