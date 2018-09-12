#ifndef WINDOWS_H
#define WINDOWS_H

#include <windows.h>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

WINBOOL SetSystemCurrentTime(int year,int month,int day,int hour,int minute,int second);
void ProofreadingBeijingTime();

#endif // WINDOWS_H
