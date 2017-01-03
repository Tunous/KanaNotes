#include "mainwindow.h"
#include "ui_mainwindow.h"

Note parseNote(QTextStream &stream, QString &noteTitle)
{
    QString noteDescription = "";

    while (!stream.atEnd()) {
        QString line = stream.readLine();

        if (line.startsWith("#ENDNOTE#")) {
            break;
        }

        noteDescription.append(line);
        noteDescription.append('\n');
    }

    noteDescription = noteDescription.trimmed();

    return Note(noteTitle, noteDescription);
}

NoteList parseList(QTextStream &stream, QString &listName)
{
    NoteList list(listName);

    while (!stream.atEnd()) {
        QString line = stream.readLine();

        if (line.startsWith("#ENDLIST#")) {
            break;
        }

        if (line.startsWith("#NOTE#")) {
            QString noteTitle = line.mid(6).trimmed();

            Note note = parseNote(stream, noteTitle);
            list.addNote(note);
        }
    }

    return list;
}

QList<NoteList> parseFile(QTextStream &stream)
{
    QList<NoteList> lists;

    while (!stream.atEnd()) {
        QString line = stream.readLine();

        if (line.startsWith("#LIST#")) {
            QString listName = line.mid(6).trimmed();

            NoteList list = parseList(stream, listName);
            lists.append(list);
        }
    }

    return lists;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString filename = QFileDialog::getOpenFileName(this, "Otwórz", QDir::currentPath(), "All files (*.*)");

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QFile::Text)) {
        QTextStream in(&file);

        lists = parseFile(in);
        file.close();
    }

    foreach (NoteList list, lists) {
        addList(list);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addList(NoteList &listt) {
    NoteListView *list = new NoteListView();
    list->setList(&listt);
    ui->listContainer->layout()->addWidget(list);
}

void MainWindow::addList()
{
    NoteListView *list = new NoteListView();
    ui->listContainer->layout()->addWidget(list);
}
