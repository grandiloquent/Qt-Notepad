#include "win.h"

void WalkProcessTree(){
    DWORD pid=0;
    // https://docs.microsoft.com/en-us/windows/desktop/api/processthreadsapi/nf-processthreadsapi-openprocess
    HANDLE hProcess=OpenProcess(SYNCHRONIZE|PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,false,pid);
    if(hProcess) {

    }
}
WINBOOL SetSystemCurrentTime(int year,int month,int day,int hour,int minute,int second){


    SYSTEMTIME t;
    GetLocalTime(&t);
    t.wYear=year;
    t.wMonth=month;
    t.wDay=day;
    t.wHour=hour;
    t.wMinute=minute;
    t.wSecond=second;
    return SetLocalTime(&t);
}
void ProofreadingBeijingTime(){
    QNetworkAccessManager* manager=new QNetworkAccessManager();
    // this,
    QObject::connect(manager,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
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
