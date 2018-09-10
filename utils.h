#ifndef UTILS_H
#define UTILS_H
#include <windows.h>
#include <QList>
#include <QString>
#include <QTextCodec>
#include <QChar>

QString SortMethods(QString &s);
QString SortLines(QString &s);
QString EncodeUnicodeEscapes(const wchar_t *input);

#endif // UTILS_H
