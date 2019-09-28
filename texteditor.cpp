#include <QFileDialog>
#include <QMessageBox>
#include <QTextCursor>
#include <QFontDatabase>
#include <QtGui>
#include <QTextEdit>
#include "texteditor.h"
#include "ui_texteditor.h"
#ifdef DEBUG
#include <QDebug>
#endif
TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
    const QFontDatabase Font;
    const QStringList fontlist=Font.families();
    ui->comboBox->addItems(fontlist);
    ui->comboBox->setCurrentText(ui->textEdit->font().family());
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(findDialog()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(save_as()));
    connect(ui->actionFind_Next, SIGNAL(triggered()), this, SLOT(find_next()));
    connect(ui->actionInsert_Image,SIGNAL(triggered()),this,SLOT(insertImage()));
    #ifdef DEBUG
    qDebug()<<"debug";
    #endif
}
void TextEditor::open_file(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    path_file=path;
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();
    const QStringList parts = file.fileName().split("/");
    const QString lastBit = parts.at(parts.size()-1);
    ui->statusBar->showMessage(lastBit);
}

void TextEditor::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;C Files (*.c *.h);;All File(*)"));
    if (fileName != "") {
       open_file(fileName);
    }
}
void TextEditor::findDialog(){
    Dialog* find=new Dialog(this,&(TextEditor::FindStringBuff));
    find->setWindowTitle("Find");
    if(find->exec()==QDialog::Accepted){
        delete find;
    }

}

void TextEditor::find(){
    QTextCursor textCursor = ui->textEdit->textCursor();
    textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
    ui->textEdit->setTextCursor(textCursor);
    TextEditor::find_next();
}
void TextEditor::find_next(){
    if(!TextEditor::FindStringBuff.isEmpty())
    ui->textEdit->find(TextEditor::FindStringBuff);
}

void TextEditor::save()
{
    if (!TextEditor::path_file.isEmpty()) {
        QFile file(TextEditor::path_file);
        if (!file.open(QIODevice::WriteOnly)) {
            TextEditor::save_as();
        } else {
            QTextStream stream(&file);
            stream <<ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }else {
 TextEditor::save_as();
}
}
void TextEditor::save_as()
{
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
    tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;C Files (*.c *.h);;All File(*.*)"));
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        } else {
            QTextStream stream(&file);
            stream <<ui->textEdit->toHtml();// toHtml for save image and text , its only text image delete
            stream.flush();
            file.close();
        }
    }

}
void TextEditor::quit(){
    if(!ui->textEdit->toPlainText().isEmpty()){
    QMessageBox msgBox;
    msgBox.setText("Warning!");
    msgBox.setInformativeText("Do you want to save the changes? ");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int res = msgBox.exec();
    if(res==QMessageBox::Yes){
        TextEditor::save();
    }
    }
        qApp->exit();
}
void TextEditor::closeEvent(QCloseEvent *event){
    TextEditor::quit();
     event->accept();
}
TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::on_horizontalSlider_valueChanged(int value)
{
    int result=value-lastzoom;
    if(result>0){
        ui->textEdit->zoomIn(result);
    }else if (result<0){
        ui->textEdit->zoomOut(-result);
    }
    lastzoom=value;
}
void TextEditor::insertImage()
{
    const QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                  ".", tr("Bitmap Files (*.bmp)\n"
                                    "JPEG (*.jpg *jpeg)\n"
                                    "GIF (*.gif)\n"
                                    "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument =   ui->textEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor =   ui->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
 }

void TextEditor::on_comboBox_activated(const QString &arg1)
{
    ui->textEdit->setFont(arg1);
}

void TextEditor::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls()) {
           QString fileName = url.toLocalFile();
           if (fileName != "") {
               TextEditor::open_file(fileName);
           }
       }
}
