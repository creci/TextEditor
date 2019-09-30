#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif
#include "texteditor.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    #ifdef DEBUG
    qDebug()<<"debug";
    #endif
    QApplication a(argc, argv);
    TextEditor w;
    w.show();
    return a.exec();
}
