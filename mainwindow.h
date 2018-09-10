#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
