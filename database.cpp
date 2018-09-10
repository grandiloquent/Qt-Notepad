#include "database.h"

Database * Database::m_instance=nullptr;

Database::Database(){
    createStructure();
}
bool Database::open(){
    return m_db.open();
}
Database* Database::instance(){
    if(!m_instance) {
        m_instance=new  Database();


    }
    return m_instance;
}
bool Database::createStructure(){
    QStringList ls;
    ls.append("CREATE TABLE IF NOT EXISTS \u0022Article\u0022 ( \u0022Id\u0022 integer primary key autoincrement not null , \u0022Title\u0022 varchar , \u0022Content\u0022 varchar , \u0022CreateAt\u0022 bigint , \u0022UpdateAt\u0022 bigint )");
}
