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
    void textChanged(const QString &text);

private slots:
    void on_removeButton_clicked();
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::NoteDialog *ui;
};

#endif // NOTEDIALOG_H
