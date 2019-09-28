#include "dialog.h"
#include "ui_dialog.h"
#include "QButtonGroup"
#include "QDebug"

Dialog::Dialog(QWidget *parent,QString *string) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(on_pushButton_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(accept()));
    findstring=string;
    ui->lineEdit->setText(*(findstring));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    *(findstring)=ui->lineEdit->text();
}
