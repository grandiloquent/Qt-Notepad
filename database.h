#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QObject>
#include <QDir>
#include <QCoreApplication>
#include "utils.h"
#include <QSqlQuery>
#include <QString>
#include <QList>
#include <QPair>

class Database : public QObject {
Q_OBJECT
public:
Database(QString fileName);
~Database();
qlonglong  insert(QString &title,QString &content);
QList<QPair<qlonglong,QString> > ListNotes();
QPair<QString,QString> Query(qlonglong id);
bool DeleteNote(qlonglong id);

private:
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
