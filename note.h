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
    void on_lineEdit_textChanged(const QString &arg1);

    void on_removeButton_clicked();

private:
    Ui::Note *ui;
    bool edited;
};

#endif // NOTE_H
