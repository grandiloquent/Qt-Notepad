#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QClipboard>
#include <QDebug>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->addAction(ui->actionCopy);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"Open File","",tr("Image Files (*.png *.jpg *.bmp)"));
}

void MainWindow::on_actionCopy_triggered()
{
    QTextCursor c=ui->plainTextEdit->textCursor();

}

void MainWindow::on_actionFormatPath_triggered()
{
    QClipboard *c = QApplication::clipboard();
    //QClipboard* c= QApplication::clipboard();
    QString str= c->text();
    if(str.trimmed().size()>0) {
        c->setText(str.replace("\\","/"));
    }

}

void MainWindow::on_actionSort_triggered()
{
    QClipboard *c = QApplication::clipboard();

    QString str= c->text();

    str= SortLines(str);
    c->setText(str);
}

void MainWindow::on_actionEscape_triggered()
{
    QString s =QApplication::clipboard()->text();
    SortMethods(s);
//    QClipboard *c=QApplication::clipboard();
//    wchar_t buf[c->text().size()*2+1];
//    c->text().toWCharArray(buf);
//    QString s=EncodeUnicodeEscapes(buf);

//    c->setText(s);

}