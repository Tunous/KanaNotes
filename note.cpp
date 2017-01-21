#include "note.h"
#include "ui_note.h"

Note::Note(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->lineEdit->setText(text);

    edited = false;
}

Note::~Note()
{
    delete ui;
}

bool Note::hasUnsavedChanges()
{
    return edited;
}

void Note::on_lineEdit_textChanged(const QString &arg1)
{
    edited = true;
}

QString Note::getText() const
{
    return ui->lineEdit->text();
}

void Note::saved()
{
    edited = false;
}
