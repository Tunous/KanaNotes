#include "note.h"
#include "ui_note.h"
#include "notelist.h"

Note::Note(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    setText(text);
    edited = false;
}

Note::~Note()
{
    delete ui;
}

bool Note::hasUnsavedChanges() const
{
    return edited;
}

void Note::markAsSaved()
{
    edited = false;
}

QString Note::getText() const
{
    return ui->textLabel->text();
}

void Note::setText(const QString &text)
{
    ui->textLabel->setText(text);
    edited = true;
}

void Note::remove()
{
    emit removeRequested(this);
}

void Note::requestMove()
{
    emit moveRequested(this);
}

void Note::requestMoveInDirection(int direction)
{
    emit moveInDirectionRequested(this, direction);
}

void Note::closeDialog()
{
    if (dialog != NULL) {
        dialog->close();
    }
}

void Note::on_editButton_clicked()
{
    dialog = new NoteDialog(getText());

    connect(dialog, SIGNAL(removeRequested()), this, SLOT(remove()));
    connect(dialog, SIGNAL(moveRequested()), this, SLOT(requestMove()));
    connect(dialog, SIGNAL(moveInDirectionRequested(int)), this, SLOT(requestMoveInDirection(int)));
    connect(dialog, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)));

    dialog->exec();

    if (dialog->getText().trimmed().isEmpty()) {
        remove();
    }

    dialog = NULL;
}
