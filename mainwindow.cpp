#include "mainwindow.h"



void MainWindow::initialize(){

    this->refreshDatabaseNames();

    QFont f("Consolas",12);
    this->ui->plainTextEdit->setFont(f);

}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->addAction(ui->actionCopy);
    ui->listWidget->addAction(ui->actionDelete);

    // Database::instance();

    this->initialize();


}
void MainWindow::on_actionClearProcesses_triggered()
{


    ClearRedundancyProcesses();


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
void MainWindow::on_actionFormatPath_triggered()
{
    QClipboard *c = QApplication::clipboard();
    //QClipboard* c= QApplication::clipboard();
    QString str= c->text();
    if(str.trimmed().size()>0) {
        c->setText(str.replace("\\","/"));
    }

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
void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"Open File","",tr("Image Files (*.png *.jpg *.bmp)"));
}
void MainWindow::on_actionOpenApplicationPath_triggered()
{
    QProcess p;
    QDesktopServices::openUrl(QUrl(QCoreApplication::applicationDirPath()));

}
void MainWindow::on_actionProofreadingBeiJingTime_triggered()
{
    ProofreadingBeijingTime();
}
void MainWindow::on_actionSave_triggered()
{
    QString str=ui->plainTextEdit->toPlainText();
    int pos= str.trimmed().indexOf('\n');

    QString title=pos>-1 ? str.trimmed().left(pos).trimmed() : str;

    if(title.startsWith(QChar('#'))) {
        int pos=title.indexOf(' ');
        if(pos>-1) {
            title=title.right(title.size()-pos).trimmed();
        }
    }
    if(currentId==0) {
        qlonglong r= currentDatabase->insert(title,str);
        currentId=r;
    }
    else{
        currentDatabase->UpdateNote(currentId,title,str);
    }
    this->setWindowTitle(title);
    refreshList();
}
void MainWindow::on_actionSort_triggered()
{
    QClipboard *c = QApplication::clipboard();

    QString str= c->text();

    str= SortLines(str);
    c->setText(str);
}
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg)
{
    reset();
    if(currentDatabase!=nullptr) {
        currentDatabase->close();
    }
    currentDatabase=new Database(ui->comboBox->currentText());
    refreshList();
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qlonglong id=item->data(Qt::UserRole).toLongLong();
    currentId=id;
    QPair<QString,QString> r=currentDatabase->Query(id);
    this->setWindowTitle(r.first);

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(r.second);
}
void MainWindow::on_plainTextEdit_textChanged()
{
    isChanged=true;
    if(!this->windowTitle().endsWith('*'))
        this->setWindowTitle(this->windowTitle()+" *");
}
void MainWindow::refreshDatabaseNames(){
    ui->comboBox->clear();
    QString dirStr= GetApplicationPath("datas");
    QDir dir(dirStr);
    QStringList allFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);//(QDir::Filter::Files,QDir::SortFlag::NoSort)
    ui->comboBox->addItems(allFiles);
}
void MainWindow::refreshList(){
    QList<QPair<qlonglong,QString> > ls=currentDatabase->ListNotes();
    ui->listWidget->clear();
    for(int i=0; i<ls.size(); i++) {
        QListWidgetItem *lwi=new QListWidgetItem();


        lwi->setData(Qt::UserRole,ls.at(i).first);
        lwi->setText(ls.at(i).second);
        ui->listWidget->addItem(lwi);
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::reset(){
    currentId=0;
    this->setWindowTitle("Notepad");
    this->ui->plainTextEdit->clear();

}
void MainWindow::on_actionDelete_triggered()
{
    qlonglong id=ui->listWidget->currentItem()->data(Qt::UserRole).toLongLong();

    currentDatabase->DeleteNote(id);
    refreshList();
}
