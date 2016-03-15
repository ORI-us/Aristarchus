#include "New_Dialog.h"
#include "ui_New_Dialog.h"

New_Dialog::New_Dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::New_Dialog)
{
    ui->setupUi(this);
}

New_Dialog::~New_Dialog()
{
    delete ui;
}
