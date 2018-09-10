#include "database.h"


Database * Database::m_instance=nullptr;

void Database::close(){
    m_db.close();
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
Database::Database(){
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    QString f("datas");
    QString dir=GetApplicationPath(f);

    if(!QDir(dir).exists()) {
        QDir().mkdir(dir);
    }
    QString fn("db.dat");
    m_db.setDatabaseName(CombinePath(dir,fn));
    createStructure();
}
bool Database::executeCommands(QStringList &commands){
    for(uint i=0; i<commands.size(); i++) {
        QSqlQuery q= m_db.exec(commands[i]);
    }
    return true;
}
Database* Database::instance(){
    if(!m_instance) {
        m_instance=new  Database();


    }
    return m_instance;
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
bool Database::commit(){
    return m_db.commit();
}
