#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "database.h"
#include "file.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "win.h"
#include <QClipboard>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QProcess>
#include <QTextBlock>


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

void on_actionProofreadingBeiJingTime_triggered();

void on_actionOpenApplicationPath_triggered();

void on_actionSave_triggered();

void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

void on_actionDelete_triggered();

private:
bool isChanged;
Ui::MainWindow *ui;
Database *currentDatabase;
qlonglong currentId;

int lastId;
void refreshDatabaseNames();
void initialize();
void refreshList();
};

#endif // MAINWINDOW_H
