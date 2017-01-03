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

BoardWidget* MainWindow::getBoard(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);
    BoardWidget *board = dynamic_cast<BoardWidget*>(widget);
    return board;
}

void MainWindow::openBoard()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open board...", QDir::currentPath(), "Text files (*.txt)");
    addBoard(fileName);
}

void MainWindow::setBoardActionsEnabled(bool enabled)
{
    ui->actionSave->setEnabled(enabled);
    ui->actionSaveAs->setEnabled(enabled);
    ui->actionCloseBoard->setEnabled(enabled);
    ui->actionCloseAllBoards->setEnabled(enabled);
}

void MainWindow::closeBoard(int index)
{
    if (index < 0) {
        return;
    }

    BoardWidget *board = getBoard(index);
    if (board->hasUnsavedChanges()) {
        // TODO: Prompt to save
        return;
    }

    ui->tabWidget->removeTab(index);

    if (ui->tabWidget->count() == 0) {
        setBoardActionsEnabled(false);
    }
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

    if (ui->tabWidget->count() == 0) {
        setBoardActionsEnabled(false);
    }
}

void MainWindow::saveBoard()
{
    getBoard(ui->tabWidget->currentIndex())->save();
}

void MainWindow::saveBoardAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Board As...", QDir::currentPath(), "Text files (*.txt)");
    if (fileName == NULL) {
        return;
    }

    getBoard(ui->tabWidget->currentIndex())->saveAs(fileName);
}

void MainWindow::createBoard()
{
    QString fileName = QFileDialog::getSaveFileName(this, "New Board...", QDir::currentPath(), "Text files (*.txt)");
    addBoard(fileName);
}

void MainWindow::addBoard(QString fileName)
{
    if (fileName == NULL) {
        return;
    }

    QFileInfo fileInfo(fileName);

    BoardWidget *board = new BoardWidget(fileName);
    ui->tabWidget->addTab(board, fileInfo.fileName());

    setBoardActionsEnabled(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeBoard(index);
}

void MainWindow::on_actionOpenBoard_triggered()
{
    openBoard();
}

void MainWindow::on_actionNewBoard_triggered()
{
    createBoard();
}

void MainWindow::on_actionSave_triggered()
{
    saveBoard();
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveBoardAs();
}

void MainWindow::on_actionCloseBoard_triggered()
{
    closeSelectedBoard();
}

void MainWindow::on_actionCloseAllBoards_triggered()
{
    closeAllBoards();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
