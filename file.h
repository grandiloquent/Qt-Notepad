#ifndef FILE_H
#define FILE_H
#include <QString>

QString formatSize(qint64 size);
qint64 dirSize(QString dirPath);
QString CombinePath(const QString &dir,const QString &fileName);
QString GetApplicationPath(const QString &fileName);

#endif
