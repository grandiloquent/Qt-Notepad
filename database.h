#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QObject>
#include <QDir>
#include <QCoreApplication>
#include "utils.h"
#include <QSqlQuery>

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
void close();
bool transaction();
bool executeCommands(QStringList &commands);
void rollback();
bool commit();
};

#endif // DATABASE_H
