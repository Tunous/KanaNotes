#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QFile>

#include "notelist.h"
#include "notelistview.h"

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QString filename, QWidget *parent = 0);
    ~BoardWidget();

    void addList(NoteList *list);

    void saveAs(QString filename);
    void save();

private slots:
    void on_addListButton_clicked();

private:
    Ui::BoardWidget *ui;
    QList<NoteList> lists;
    QString savedFilename;

    void addEmptyList();

    void loadFromFile(QString filename);

    QList<NoteList> parseFile(QTextStream &stream);
    NoteList parseList(QTextStream &stream, QString &listName);
    Note parseNote(QTextStream &stream, QString &noteTitle);
};

#endif // BOARDWIDGET_H
