#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "utils.h"
#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = 0);
~MainWindow();

private slots:
void on_actionOpen_triggered();

void on_actionCopy_triggered();

void on_actionFormatPath_triggered();

void on_actionSort_triggered();

void on_actionEscape_triggered();

void on_actionFormatCode_triggered();

void on_comboBox_currentIndexChanged(const QString &arg1);

void on_actionFormatTitle_triggered();

void on_plainTextEdit_textChanged();

void on_actionClearProcesses_triggered();

void on_actionFormatConstName_triggered();

private:
bool isChanged;
Ui::MainWindow *ui;
void refreshDatabaseNames();
};

#endif // MAINWINDOW_H
