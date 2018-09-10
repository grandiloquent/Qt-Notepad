#include "utils.h"
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

bool compareString(const QString&v1,const QString &v2){
    return v1<v2;
}
QString EncodeUnicodeEscapes(const wchar_t *input){
    std::wstring output;
    QString result;

    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );

    for( uint i = 0; wcslen( input ) > i; ++i )
    {
        if( isascii( input[ i ] )&&input[i]!=L'"' )
        {
            output.reserve( output.size() + 1 );
            output += input[ i ];
        } else {
            wchar_t code[ 7 ];
            swprintf( code, 7, L"\\u%0.4X", input[ i ] );
            output.reserve( output.size() + 7 ); // "\u"(2) + 5(uint max digits capacity)
            output += code;
        }
    }

    result.reserve( output.size() );
    result.append( QString::fromStdWString( output ) );
    return result;
}
WINBOOL SetSystemTime(int hour,int minute){
    SYSTEMTIME t;
    GetLocalTime(&t);
    t.wHour=hour;
    t.wMinute=minute;
    return SetLocalTime(&t);
}
QString SortLines(QString &s){
    QStringList list;
    list=s.split('\n',QString::SplitBehavior::SkipEmptyParts);
    for(int i=0; i<list.size(); i++) {
        list[i]=list[i].trimmed();
    }
    std::sort(list.begin(),list.end(),compareString);

    return list.join("\n");

}
QString SortMethods(QString &s){
    QChar c1=QChar('{');
    QChar c2=QChar('}');
    uint c=0;
    QStringList ls;
    QString n;
    for(uint i=0; i<s.size(); i++) {
        n.append(s[i]);
        if(s[i]==c1) {
            c++;
        }else if(s[i]==c2) {
            c--;
            if(c==0) {
                ls.append(n.trimmed());

                n.clear();
            }
        }

    }
    std::sort(ls.begin(),ls.end(),[](const QString &v1,const QString &v2) -> bool {

        QString vs1,vs2;
        int p1= v1.indexOf('(');
        if(p1>-1) {
                vs1=v1.left(p1);
        }else{
                vs1=v1;
        }
        p1= vs1.indexOf(' ');
        if(p1>-1) {
                vs1=vs1.right(vs1.size()-p1-1);
        }
        int p2= v2.indexOf('(');
        if(p2>-1) {
                vs2=v2.left(p2);
        }else{
                vs2=v2;
        }


        p2= vs2.indexOf(' ');
        if(p2>-1) {
                vs2=vs2.right(vs2.size()-p2-1);
        }


        return vs1.compare(vs2,Qt::CaseInsensitive)<0;
    });
    return ls.join('\n');
}
QString CombinePath(const QString &dir,const QString &fileName){
    return QDir::cleanPath(dir+QDir::separator()+fileName);
}
QString GetApplicationPath(const QString &fileName){
    return CombinePath(QCoreApplication::applicationDirPath(),fileName);
}
