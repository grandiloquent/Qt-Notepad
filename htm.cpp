#include "htm.h"
#include <QXmlQuery>
#include <QDir>

#include <QFileInfoList>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QIODevice>


void ExtractSourceCode(QString dirPath){
    QDir dir(dirPath);
    QStringList filters;
    filters<<"*.htm"<<"*.html"<<"*.xhtml";
    dir.setFilter(QDir::Files|QDir::Hidden);
    dir.setNameFilters(filters);
    QFileInfoList ls=dir.entryInfoList();

    QXmlQuery q;

    for(int i=0; i<ls.size(); ++i) {
        QFileInfo fileInfo=ls.at(i);
        QFile f(fileInfo.absolutePath());
        if(f.open(QIODevice::ReadOnly)) {
            QTextStream in(&f);
            QString str= in.readAll();

            f.close();
        }
    }
}

