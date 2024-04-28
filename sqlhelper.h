#ifndef SQLHELPER_H
#define SQLHELPER_H
#include<QtSql/QSqlDatabase>
#include<string>
#include "global_wjl.h"
using namespace std;
class SqlHelper
{
public:
    static bool connect(const string ip,const string database,const string username,const string pwd);
    static bool queryUser(const string user,string password,User& userData);
private:
     SqlHelper();
    static QSqlDatabase db;

};

#endif // SQLHELPER_H
