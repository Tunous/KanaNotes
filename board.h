#ifndef BOARD_H
#define BOAR_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>

#include "notelist.h"

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

private slots:
    void on_addListButton_clicked();

private:
    Ui::Board *ui;
    QString savedFileName;

    void addEmptyList();

    void loadFromFile(QString filename);

    void parseFile(QTextStream &stream);
    NoteList *getList(int index);
};

#endif // BOARD_H
