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
    void addNote(QWidget *scrollArea);

private:
    QWidget *titleRow;
    QLineEdit *nameInput;
    QToolButton *actionsButton;

    QScrollArea *scrollArea;

    QPushButton *addNoteButton;
};

#endif // NOTESLIST_H
