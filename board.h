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

    void addList(NoteList *list);

    void saveAs(QString fileName);
    void save();

    bool hasUnsavedChanges();
    QString getName();

    QList<QString> getListNames();

private slots:
    void on_addListButton_clicked();
    void removeList(NoteList *list);
    void moveNote(NoteList *list, Note *note);
    void moveNoteInDirection(NoteList *list, Note *note, int direction);

private:
    Ui::Board *ui;
    QString savedFileName;
    bool edited;

    void addEmptyList();
    int selectList();

    void loadFromFile(QString filename);

    void parseFile(QTextStream &stream);
    NoteList *getList(int index);
};

#endif // BOARD_H
