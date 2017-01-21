#include "board.h"
#include "ui_board.h"

Board::Board(QString fileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    loadFromFile(fileName);
}

Board::~Board()
{
    delete ui;
}

bool Board::hasUnsavedChanges()
{
    QLayout *layout = ui->listContainer->layout();
    for (int i = 0; i < layout->count(); i++) {
        NoteList *list = getList(i);
        if (list != NULL && list->hasUnsavedChanges()) {
            return true;
        }
    }

    return false;
}

NoteList* Board::getList(int index)
{
    QLayout *layout = ui->listContainer->layout();
    return dynamic_cast<NoteList*>(layout->itemAt(index)->widget());
}

void Board::loadFromFile(QString fileName)
{
    savedFileName = fileName;

    QFile file(fileName);
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
    saveAs(savedFileName);
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
        NoteList *list = getList(i);

        if (list != NULL) {
            out << "# " << list->getName() << endl;

            foreach (QString note, list->getNotes()) {
                out << "- " << note << endl;
            }

            out << endl;

            list->saved();
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

QString Board::getName()
{
    QFileInfo fileInfo(savedFileName);
    return fileInfo.fileName();
}
