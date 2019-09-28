#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <QMainWindow>
#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QShortcut>
#include "QMessageBox"
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include "dialog.h"


namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();
    TextEditor(const TextEditor &ptr);


private:
    Ui::TextEditor *ui;
    QAction *exitAction;
    QString path_file;
    QString FindStringBuff;
    int lastzoom=0;
    void closeEvent(QCloseEvent *event);
    void dropEvent(QDropEvent *event);
    void open_file(QString path);

private slots:
    void open();
    void save();
    void save_as();
    void quit();
    void findDialog();
    void on_horizontalSlider_valueChanged(int value);
    void on_comboBox_activated(const QString &arg1);
    void insertImage();
public slots:
    void find();
    void find_next();
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event){
        if(event->mimeData()->hasUrls()){
            event->acceptProposedAction();
        }
    }

};

#endif // TEXTEDITOR_H
