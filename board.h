#ifndef BOARD_H
#define BOAR_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>

#include "notelist.h"
#include "selectlistdialog.h"

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QString filename, QWidget *parent = 0);
    ~Board();

    bool hasUnsavedChanges();
    void addList(NoteList *list);

    void saveAs(QString fileName);
    void save();

    QString getName();

private slots:
    void on_addListButton_clicked();

    void destroyList(NoteList *list);

    void moveNote(NoteList *list, Note *note);
    void moveNoteInDirection(NoteList *list, Note *note, int direction);
    void moveListInDirection(NoteList *list, int direction);

private:
    Ui::Board *ui;
    QString savedFileName;
    bool edited;

    void loadFromFile(QString fileName);
    void parseFile(QTextStream &stream);

    NoteList *getList(int index);

    void addNewList();
    int selectList(int currentIndex);
};

#endif // BOARD_H
