#ifndef UTILS_H
#define UTILS_H
#include <win.h>
#include <QList>
#include <QString>
#include <QTextCodec>
#include <QChar>

typedef QString (*OnClipboardStringCallback)(QString);

void OnClipboardString(OnClipboardStringCallback *callback);
QString SortMethods(QString &s);
QString SortLines(QString &s);
QString EncodeUnicodeEscapes(const wchar_t *input);
QString CombinePath(const QString &dir,const QString &fileName);
QString GetApplicationPath(const QString &fileName);
bool ClearRedundancyProcesses();
WINBOOL SetSystemCurrentTime(int year,int month,int day,int hour,int minute,int second);

#endif // UTILS_H
