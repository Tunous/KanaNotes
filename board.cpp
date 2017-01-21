#include "board.h"
#include "ui_board.h"

Board::Board(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    loadFromFile(filename);
}

Board::~Board()
{
    delete ui;
}

bool Board::hasUnsavedChanges()
{
    for (int i = 0; i < ui->listContainer->layout()->count(); i++) {
        NoteList *list = dynamic_cast<NoteList*>(ui->listContainer->layout()->itemAt(i));
        if (list != NULL && list->hasUnsavedChanges()) {
            return true;
        }
    }

    return false;
}

void Board::loadFromFile(QString filename)
{
    savedFilename = filename;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug() << "Error loading board from file";
        return;
    }

    QTextStream in(&file);
    parseFile(in);
    file.close();
}

void Board::addList(NoteList *list)
{
    ui->listContainer->layout()->addWidget(list);
}

void Board::addEmptyList()
{
    addList(new NoteList(""));
}

void Board::save()
{
    saveAs(savedFilename);
}

void Board::saveAs(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    QTextStream out(&file);

    QLayout *layout = ui->listContainer->layout();
    for (int i = 0; i < layout->count(); i++) {
        QWidget *widget = layout->itemAt(i)->widget();
        NoteList *list = dynamic_cast<NoteList*>(widget);

        if (list != NULL) {
            out << "# " << list->getName() << endl;

            foreach (QString note, list->getNotes()) {
                out << "- " << note << endl;
            }

            out << endl;
        }
    }
    file.flush();
    file.close();
}

void Board::parseFile(QTextStream &stream)
{
    QString line;
    QString listName = "";
    QList<QString> *notes = new QList<QString>;

    while (!stream.atEnd()) {
        line = stream.readLine();

        if (line.startsWith("#")) {
            if (listName != "") {
                addList(new NoteList(listName, notes));
                notes = new QList<QString>();
            }

            listName = line.mid(1).trimmed();
        }

        if (line.startsWith("-")) {
            notes->append(line.mid(1).trimmed());
        }
    }

    if (listName != "") {
        addList(new NoteList(listName, notes));
    }
}

void Board::on_addListButton_clicked()
{
    addEmptyList();
}
