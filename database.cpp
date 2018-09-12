#include "database.h"
#include <QSqlQuery>
#include <QDateTime>





void Database::close(){
    m_db.close();
}
bool Database::commit(){
    return m_db.commit();
}
bool Database::createStructure(){
    QStringList ls;
    ls.append("CREATE TABLE IF NOT EXISTS \u0022Article\u0022 ( \u0022Id\u0022 integer primary key autoincrement not null , \u0022Title\u0022 varchar , \u0022Content\u0022 varchar , \u0022CreateAt\u0022 bigint , \u0022UpdateAt\u0022 bigint )");
    if(!this->open())
    {return false;}
    if(!this->transaction()) {
        this->close();
        return false;
    }
    if(!this->executeCommands(ls))
    {
        this->rollback();
        this->close();
        return false;
    }
    bool c=this->commit();
    this->close();
    return c;
}
Database::Database(QString fileName){
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    QString f("datas");
    QString dir=GetApplicationPath(f);

    if(!QDir(dir).exists()) {
        QDir().mkdir(dir);
    }

    m_db.setDatabaseName(CombinePath(dir,fileName));
    createStructure();
}
bool Database::executeCommands(QStringList &commands){
    for(uint i=0; i<commands.size(); i++) {
        QSqlQuery q= m_db.exec(commands[i]);
    }
    return true;
}
qlonglong Database::insert(QString &title,QString &content){
    if(!this->open()) return -1;
    if(!this->transaction()) {
        this->close();
        return -1;
    }
    QSqlQuery q;
    q.prepare("INSERT INTO Article (Title, Content, CreateAt,UpdateAt) "
              "VALUES (:title, :content, :createAt, :updateAt)");
    q.bindValue(":title",title);
    q.bindValue(":content",content);
    q.bindValue(":createAt",QDateTime::currentSecsSinceEpoch());
    q.bindValue(":updateAt",QDateTime::currentSecsSinceEpoch());
    q.exec();
    bool c=this->commit();
    qlonglong r=c ? q.lastInsertId().toLongLong() : -1;
    this->close();
    return r;

}

bool Database::open(){
    return m_db.open();
}
void Database::rollback(){
    m_db.rollback();

}
bool Database::transaction(){
    return m_db.transaction();
}
Database::~Database(){

}
