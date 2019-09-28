#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "texteditor.h"
#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr,QString *string=nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QString *findstring;
private slots:
    void on_pushButton_clicked();
signals: void signalFromDialog();
};

#endif // DIALOG_H
