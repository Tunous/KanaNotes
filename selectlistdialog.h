#ifndef SELECTLISTDIALOG_H
#define SELECTLISTDIALOG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class SelectListDialog;
}

class SelectListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectListDialog(const QStringList &listNames, int currentIndex, QWidget *parent = 0);
    ~SelectListDialog();

    int selectedIndex() const;

private:
    Ui::SelectListDialog *ui;
};

#endif // SELECTLISTDIALOG_H
