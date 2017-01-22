#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include <QDialog>

namespace Ui {
class NoteDialog;
}

class NoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteDialog(QString text, QWidget *parent = 0);
    ~NoteDialog();

    QString getText();

signals:
    void removeRequested();
    void moveRequested();
    void moveInDirectionRequested(int direction);
    void textChanged(const QString &text);

private slots:
    void on_removeButton_clicked();
    void on_lineEdit_textEdited(const QString &arg1);

    void on_moveToListButton_clicked();

    void on_moveLeftButton_clicked();

    void on_moveRightButton_clicked();

private:
    Ui::NoteDialog *ui;
};

#endif // NOTEDIALOG_H
