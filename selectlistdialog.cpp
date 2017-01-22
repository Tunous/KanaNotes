#include "selectlistdialog.h"
#include "ui_selectlistdialog.h"

SelectListDialog::SelectListDialog(const QStringList &listNames, int currentIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectListDialog)
{
    ui->setupUi(this);

    QStringListModel *model = new QStringListModel(listNames);
    ui->listView->setModel(model);

    QModelIndex index = model->index(currentIndex);
    ui->listView->setCurrentIndex(index);
}

SelectListDialog::~SelectListDialog()
{
    delete ui;
}

int SelectListDialog::selectedIndex() const
{
    return ui->listView->currentIndex().row();
}
