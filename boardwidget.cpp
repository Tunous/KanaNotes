#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget),
    unsavedChanges(false)
{
    ui->setupUi(this);

    loadFromFile(filename);
}

BoardWidget::~BoardWidget()
{
    delete ui;
}

bool BoardWidget::hasUnsavedChanges()
{
    return unsavedChanges;
}

void BoardWidget::loadFromFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug() << "Error loading board from file";
        return;
    }

    QTextStream in(&file);
    lists = parseFile(in);
    file.close();

    foreach (NoteList list, lists) {
        addList(&list);
    }

    savedFilename = filename;
}

void BoardWidget::addList(NoteList *list)
{
    NoteListView *listView = new NoteListView(list);
    ui->listContainer->layout()->addWidget(listView);
}

void BoardWidget::addEmptyList()
{
    addList(new NoteList(""));
}

void BoardWidget::save()
{
    saveAs(savedFilename);
}

void BoardWidget::saveAs(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    QTextStream out(&file);
    foreach (NoteList list, lists) {
        out << "#LIST# " << list.getName().trimmed() << '\n';

        foreach (Note note, list.getNotes()) {
            out << "\n#NOTE# " << note.getTitle().trimmed() << '\n';
            out << note.getDescription() << '\n';
            out << "#ENDNOTE#\n";
        }

        out << "\n#ENDLIST#\n\n";
    }
    file.flush();
    file.close();
}

QList<NoteList> BoardWidget::parseFile(QTextStream &stream)
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

NoteList BoardWidget::parseList(QTextStream &stream, QString &listName)
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

Note BoardWidget::parseNote(QTextStream &stream, QString &noteTitle)
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

void BoardWidget::on_addListButton_clicked()
{
    addEmptyList();
}
