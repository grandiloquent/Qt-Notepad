#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QObject>


class Database : public QObject {
Q_OBJECT
public:
static Database *instance();

private:
static Database *m_instance;
Database();
~Database(){
};
QSqlDatabase m_db;
bool createStructure();
bool open();
bool close();
bool executeCommands(QStringList &commands);

};

#endif // DATABASE_H
