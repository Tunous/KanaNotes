#include "note.h"
#include "ui_note.h"
#include "notelist.h"

Note::Note(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->textLabel->setText(text);

    QMenu *menu = new QMenu(this);
    menu->addAction(ui->actionRemove);
    menu->addAction(ui->actionMoveLeft);
    menu->addAction(ui->actionMoveUp);
    menu->addAction(ui->actionMoveRight);
    menu->addAction(ui->actionMoveDown);

    ui->actionsButton->setMenu(menu);

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

void Note::on_actionMoveLeft_triggered()
{

}

void Note::on_actionMoveUp_triggered()
{

}

void Note::on_actionMoveRight_triggered()
{

}

void Note::on_actionMoveDown_triggered()
{

}

void Note::on_actionRemove_triggered()
{
    emit removeRequested(this);
}
