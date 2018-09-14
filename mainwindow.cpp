#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBlock>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->addAction(ui->actionCopy);

    this->refreshDatabaseNames();
    // Database::instance();


}
void MainWindow::refreshDatabaseNames(){
    ui->comboBox->clear();
    QString dirStr= GetApplicationPath("datas");
    QDir dir(dirStr);
    QStringList allFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);//(QDir::Filter::Files,QDir::SortFlag::NoSort)
    ui->comboBox->addItems(allFiles);
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
    QTextCursor cursor=ui->plainTextEdit->textCursor();
    if(cursor.selectedText().isNull()) {




        int line=ui->plainTextEdit->document()->findBlock(cursor.position()).blockNumber();

        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor,  line);
        cursor.select(QTextCursor::LineUnderCursor);
        // cursor.removeSelectedText();

        ui->plainTextEdit->setTextCursor(cursor);

    }
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

    QClipboard *c=QApplication::clipboard();
    wchar_t buf[c->text().size()*2+1];
    c->text().toWCharArray(buf);
    QString s=EncodeUnicodeEscapes(buf);

    c->setText(s);

}

void MainWindow::on_actionFormatCode_triggered()
{
    QClipboard *c=QApplication::clipboard();
    QString s =c->text();
    s= SortMethods(s);
    c->setText(s);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg)
{
    qDebug()<<arg;
}

void MainWindow::on_actionFormatTitle_triggered()
{
    QTextCursor c=ui->plainTextEdit->textCursor();
    int start=c.position();
    QString str= ui->plainTextEdit->toPlainText();

    if(start==0) {


    }else{
        while(start>0) {
            if(str[start]=='\n')
            {
                start++;

                break;
            }
            start--;
        }
        qDebug()<<start<<" "<<str[start];
    }
    c.setPosition(start);
    if(str[start]=='#')
        c.insertText("#");
    else
        c.insertText("# ");

    //
    //ui->plainTextEdit->setTextCursor(c);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    isChanged=true;
    if(!this->windowTitle().endsWith('*'))
        this->setWindowTitle(this->windowTitle()+" *");
}

void MainWindow::on_actionClearProcesses_triggered()
{


    ClearRedundancyProcesses();
    int r= SetSystemCurrentTime(1,38);
    qDebug()<<r;
}

void MainWindow::on_actionFormatConstName_triggered()
{
    QClipboard *c=QApplication::clipboard();
    QString s =c->text();
    QString t=s;
    int cx=0;
    for(uint i=0; i<s.size(); i++) {
        if(i!=0&&s[i].isUpper()) {
            t.insert(i+cx,'_');
            cx++;
        }
    }
    c->setText(t.toUpper());
}


void MainWindow::on_actionProofreadingBeiJingTime_triggered()
{
    QNetworkAccessManager* manager=new QNetworkAccessManager();
    QObject::connect(manager,&QNetworkAccessManager::finished,this,[=](QNetworkReply *reply){
        if(reply->error()) {
                qDebug()<<reply->errorString();
                return;
        }
        QString res=reply->readAll();
        uint v=res.left(10).toLong();

        QDateTime time;

        time.setTime_t(v);

        SetSystemCurrentTime(time.date().year(),time.date().month(),time.date().day(),time.time().hour(),time.time().minute(),time.time().second());
    });
    QNetworkRequest request;
    request.setUrl(QUrl("https://bjtime.cn/nt.asp"));
    manager->get(request);
}
