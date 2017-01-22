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

Board* MainWindow::getBoard(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);
    return dynamic_cast<Board*>(widget);
}

void MainWindow::setBoardActionsEnabled(bool enabled)
{
    ui->actionSave->setEnabled(enabled);
    ui->actionSaveAs->setEnabled(enabled);
    ui->actionCloseBoard->setEnabled(enabled);
    ui->actionCloseAllBoards->setEnabled(enabled);
}

void MainWindow::openBoard()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "Open board...",
                QDir::currentPath(),
                "Text files (*.txt)");
    addBoard(fileName);
}

void MainWindow::closeBoard(int index)
{
    if (index < 0) {
        return;
    }

    Board *board = getBoard(index);
    if (!canClose(board)) {
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
    int tabsCount = ui->tabWidget->count();

    for (int i = 0; i < tabsCount; i++) {
        if (canClose(getBoard(0))) {
            ui->tabWidget->removeTab(0);
        } else {
            return;
        }
    }

    if (ui->tabWidget->count() == 0) {
        setBoardActionsEnabled(false);
    }
}

bool MainWindow::canClose(Board *board)
{
    if (!board->hasUnsavedChanges()) {
        return true;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Unsaved changes",
                "You have unsaved changes for \"" + board->getName() + "\". Save?",
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    switch (reply) {
    case QMessageBox::Yes:
        board->save();
        break;

    case QMessageBox::No:
        break;

    default:
        return false;
    }

    return true;
}

void MainWindow::saveBoard()
{
    getBoard(ui->tabWidget->currentIndex())->save();
}

void MainWindow::saveBoardAs()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "Save as...",
                QDir::currentPath(),
                "Text files (*.txt)");

    if (fileName == NULL) {
        return;
    }

    getBoard(ui->tabWidget->currentIndex())->saveAs(fileName);
}

void MainWindow::createBoard()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "New board...",
                QDir::currentPath(),
                "Text files (*.txt)");

    addBoard(fileName, true);
}

void MainWindow::addBoard(QString fileName, bool createLists)
{
    if (fileName == NULL) {
        return;
    }

    QFileInfo fileInfo(fileName);

    Board *board = new Board(fileName);
    int index = ui->tabWidget->addTab(board, fileInfo.fileName());
    ui->tabWidget->setCurrentIndex(index);

    setBoardActionsEnabled(true);

    if (createLists) {
        board->addList(new NoteList("To Do"));
        board->addList(new NoteList("Doing"));
        board->addList(new NoteList("Done"));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        Board *board = getBoard(i);
        if (!canClose(board)) {
            event->ignore();
        }
    }
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
