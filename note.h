#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QDialog>

#include "notedialog.h"

namespace Ui {
class Note;
}

class Note : public QWidget
{
    Q_OBJECT

public:
    explicit Note(QString text = "", QWidget *parent = 0);
    ~Note();

    bool hasUnsavedChanges() const;
    QString getText() const;

    void markAsSaved();
    void closeDialog();

signals:
    void removeRequested(Note *note);
    void moveRequested(Note *note);

private slots:
    void on_editButton_clicked();

    void setText(const QString &text);
    void remove();
    void requestMove();

private:
    Ui::Note *ui;
    bool edited;
    NoteDialog *dialog = NULL;
};

#endif // NOTE_H
