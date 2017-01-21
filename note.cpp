#include "note.h"
#include "ui_note.h"
#include "notelist.h"

Note::Note(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->textLabel->setText(text);

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

QString Note::getText() const
{
    return ui->textLabel->text();
}

void Note::saved()
{
    edited = false;
}

void Note::on_removeButton_clicked()
{
    emit removeRequested(this);
}
