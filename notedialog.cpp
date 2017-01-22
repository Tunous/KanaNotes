#include "notedialog.h"
#include "ui_notedialog.h"

NoteDialog::NoteDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(text);
}

NoteDialog::~NoteDialog()
{
    delete ui;
}

QString NoteDialog::getText()
{
    return ui->lineEdit->text();
}

void NoteDialog::on_removeButton_clicked()
{
    emit removeRequested();
    close();
}

void NoteDialog::on_lineEdit_textEdited(const QString &arg1)
{
    emit textChanged(arg1.trimmed());
}

void NoteDialog::on_moveToListButton_clicked()
{
    emit moveRequested();
}
