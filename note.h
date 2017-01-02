#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note
{
public:
    Note(QString title, QString description);
    Note(QString title);

    QString getTitle();
    QString getDescription();
    void setTitle(QString title);
    void setDescription(QString description);

private:
    QString title;
    QString description;
};

#endif // NOTE_H
