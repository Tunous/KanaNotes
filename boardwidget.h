#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QFile>

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

    void addList(NoteListView *list);

    void saveAs(QString fileName);
    void save();

    bool hasUnsavedChanges();

private slots:
    void on_addListButton_clicked();

private:
    Ui::BoardWidget *ui;
    QString savedFilename;

    void addEmptyList();

    void loadFromFile(QString filename);

    void parseFile(QTextStream &stream);
};

#endif // BOARDWIDGET_H
