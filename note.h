#ifndef NOTE_H
#define NOTE_H

#include <QWidget>

namespace Ui {
class Note;
}

class Note : public QWidget
{
    Q_OBJECT

public:
    explicit Note(QString text = "", QWidget *parent = 0);
    ~Note();

    bool hasUnsavedChanges();
    QString getText() const;
    void saved();

signals:
    void removeRequested(Note *note);

private slots:
    void on_actionMoveLeft_triggered();
    void on_actionMoveUp_triggered();
    void on_actionMoveRight_triggered();
    void on_actionMoveDown_triggered();
    void on_actionRemove_triggered();

private:
    Ui::Note *ui;
    bool edited;
};

#endif // NOTE_H
