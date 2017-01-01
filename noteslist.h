#ifndef NOTESLIST_H
#define NOTESLIST_H

#include <QtWidgets>

class NotesList : public QWidget
{
    Q_OBJECT
public:
    explicit NotesList(QWidget *parent = 0);

signals:

public slots:
    void showActions();
    void addNote();

private:
    QWidget *titleRow;
    QLineEdit *nameInput;
    QToolButton *actionsButton;

    QWidget *notesContainer;
    QScrollArea *scrollArea;

    QPushButton *addNoteButton;
};

#endif // NOTESLIST_H
