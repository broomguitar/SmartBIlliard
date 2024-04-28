#include "sqlhelper.h"
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/qsqldriver.h>
SqlHelper::SqlHelper()
{

}
QSqlDatabase SqlHelper::db;
bool SqlHelper::connect(const string ip,const string database,const string username,const string pwd)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(QString::fromStdString(ip));
    db.setDatabaseName(QString::fromStdString(database));
    db.setUserName(QString::fromStdString(username));
    db.setPassword(QString::fromStdString(pwd));
    if(!db.open()){
        QMessageBox::warning(nullptr,"警告",db.lastError().text());
        return false;
    }
    return true;
}
bool SqlHelper::queryUser(const string user,const string pwd,User& userData)
{
    string sql="select * from user where username='"+user+"' and password='"+pwd+"'";
    QSqlQuery query;
    int numRows;
    if(!query.exec(QString::fromStdString(sql)))
    {
        QMessageBox::warning(nullptr,"警告",query.lastError().text());
    }
    while (query.next()) {
        userData.Id=query.value(0).toInt();
        userData.UserName=query.value(1).toString().toStdString();
        userData.Role=User::ROLE(query.value(2).toInt());
        userData.Password=query.value(3).toString().toStdString();
        userData.Memo=query.value(4).toString().toStdString();
        userData.ProfilePhoto=query.value(5).toString().toStdString();
        userData.Gender=User::GENDER(query.value(6).toInt());
        userData.IsVip=query.value(7).toInt()==1;
        userData.IsValid=query.value(8).toInt()==1;
    }
    QSqlDatabase defaultDB = QSqlDatabase::database();
    if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize)) {
        numRows = query.size();
    } else {
        query.last();
        numRows = query.at() + 1;
    }
    return numRows>0;
}
