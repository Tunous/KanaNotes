#include "boardwidget.h"
#include "ui_boardwidget.h"

BoardWidget::BoardWidget(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
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
    for (int i = 0; i < ui->listContainer->layout()->count(); i++) {
        NoteListView *list = dynamic_cast<NoteListView*>(ui->listContainer->layout()->itemAt(i));
        if (list != NULL && list->hasUnsavedChanges()) {
            return true;
        }
    }

    return false;
}

void BoardWidget::loadFromFile(QString filename)
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

void BoardWidget::addList(NoteListView *list)
{
    ui->listContainer->layout()->addWidget(list);
}

void BoardWidget::addEmptyList()
{
    addList(new NoteListView(""));
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

    QLayout *layout = ui->listContainer->layout();
    for (int i = 0; i < layout->count(); i++) {
        QWidget *widget = layout->itemAt(i)->widget();
        NoteListView *list = dynamic_cast<NoteListView*>(widget);

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

void BoardWidget::parseFile(QTextStream &stream)
{
    QString line;
    QString listName = "";
    QList<QString> *notes = new QList<QString>;

    while (!stream.atEnd()) {
        line = stream.readLine();

        if (line.startsWith("#")) {
            if (listName != "") {
                addList(new NoteListView(listName, notes));
                notes = new QList<QString>();
            }

            listName = line.mid(1).trimmed();
        }

        if (line.startsWith("-")) {
            notes->append(line.mid(1).trimmed());
        }
    }

    if (listName != "") {
        addList(new NoteListView(listName, notes));
    }
}

void BoardWidget::on_addListButton_clicked()
{
    addEmptyList();
}
