#include "board.h"
#include "ui_board.h"

Board::Board(QString fileName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board),
    edited(false)
{
    ui->setupUi(this);

    loadFromFile(fileName);
}

Board::~Board()
{
    delete ui;
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

    edited = false;
}

void Board::parseFile(QTextStream &stream)
{
    QString listName = "";
    QList<QString> *notes = new QList<QString>;

    while (!stream.atEnd()) {
        QString line = stream.readLine();

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

NoteList* Board::getList(int index)
{
    QLayout *layout = ui->listContainer->layout();
    return dynamic_cast<NoteList*>(layout->itemAt(index)->widget());
}

QString Board::getName()
{
    QFileInfo fileInfo(savedFileName);
    return fileInfo.fileName();
}

bool Board::hasUnsavedChanges()
{
    if (edited) {
        return true;
    }

    QLayout *layout = ui->listContainer->layout();
    for (int i = 0; i < layout->count(); i++) {
        if (getList(i)->hasUnsavedChanges()) {
            return true;
        }
    }

    return false;
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

    edited = false;
}

void Board::addList(NoteList *list)
{
    connect(list, SIGNAL(removeRequested(NoteList*)), this, SLOT(destroyList(NoteList*)));
    connect(list, SIGNAL(moveNoteRequested(NoteList*,Note*)), this, SLOT(moveNote(NoteList*,Note*)));
    connect(list, SIGNAL(moveNoteInDirectionRequested(NoteList*,Note*,int)), this, SLOT(moveNoteInDirection(NoteList*,Note*,int)));
    connect(list, SIGNAL(moveInDirectionRequested(NoteList*,int)), this, SLOT(moveListInDirection(NoteList*,int)));

    ui->listContainer->layout()->addWidget(list);

    edited = true;
}

void Board::addEmptyList()
{
    addList(new NoteList(""));
}

void Board::destroyList(NoteList *list)
{
    list->deleteLater();
    edited = true;
}

int Board::selectList(int currentIndex)
{
    QStringList listNames;
    QLayout *listsLayout = ui->listContainer->layout();

    for (int i = 0; i < listsLayout->count(); i++) {
        listNames.append(getLis(i)->getName());
    }

    SelectListDialog *dialog = new SelectListDialog(listNames, currentIndex, this);
    int result = dialog->exec();

    if (result == QDialog::Accepted) {
        return dialog->selectedIndex();
    }

    return -1;
}

void Board::moveNote(NoteList *list, Note *note)
{
    int currentIndex = ui->listContainer->layout()->indexOf(list);
    int newIndex = selectList(currentIndex);
    if (newIndex < 0 || newIndex == currentIndex) return;

    list->removeNote(note);
    getList(newIndex)->addNote(note);
}

void Board::moveNoteInDirection(NoteList *list, Note *note, int direction)
{
    QLayout *listsLayout = ui->listContainer->layout();
    int currentIndex = listsLayout->indexOf(list);

    int newIndex = currentIndex;
    if (direction < 0 && currentIndex > 0) {
        newIndex -= 1;
    } else if (direction > 0 && currentIndex < listsLayout->count() - 1) {
        newIndex += 1;
    } else {
        return;
    }

    list->removeNote(note);
    getList(newIndex)->addNote(note);
}

void Board::moveListInDirection(NoteList *list, int direction)
{
    QLayout *listsLayout = ui->listContainer->layout();
    int currentIndex = listsLayout->indexOf(list);

    int count = listsLayout->count();

    if (direction < 0 && currentIndex > 0) {
        QLayoutItem *item = listsLayout->takeAt(currentIndex - 1);
        listsLayout->addItem(item);

        for (int i = 0; i < count - currentIndex - 1; i++) {
            item = listsLayout->takeAt(currentIndex);
            listsLayout->addItem(item);
        }
    } else if (direction > 0 && currentIndex < count - 1) {
        QLayoutItem *item = listsLayout->takeAt(currentIndex);
        listsLayout->addItem(item);

        for (int i = 0; i < count - currentIndex - 2; i++) {
            item = listsLayout->takeAt(currentIndex + 1);
            listsLayout->addItem(item);
        }
    }
}

void Board::on_addListButton_clicked()
{
    addEmptyList();
}
