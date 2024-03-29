#ifndef DIALOG_H
#define DIALOG_H
#ifdef DEBUG
#include <QDebug>
#endif
#include <QDialog>
#include "texteditor.h"

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
