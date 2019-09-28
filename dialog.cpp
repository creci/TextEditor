#include <QButtonGroup>
#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent,QString *string) :
    QDialog(parent),
    ui(new Ui::Dialog),findstring(string)
{
    ui->setupUi(this);
    this->setParent(nullptr);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(on_pushButton_clicked()));
    connect(ui->pushButton, SIGNAL(clicked()), parent,SLOT(find()));
    connect(ui->pushButton_2, SIGNAL(clicked()), parent,SLOT(find_next()));
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
