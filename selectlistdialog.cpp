#include "selectlistdialog.h"
#include "ui_selectlistdialog.h"

SelectListDialog::SelectListDialog(const QStringList &listNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectListDialog)
{
    ui->setupUi(this);

    QStringListModel *model = new QStringListModel(listNames);
    ui->listView->setModel(model);

    QModelIndex index = model->index(0);
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
