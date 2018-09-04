#ifndef MYSQL_H
#define MYSQL_H

#include "mysql_global.h"
#include "data_global.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextCodec>
class MYSQLSHARED_EXPORT  MySql
{

public:
    MySql();
    ///////////////数据库启停/////////////////////////////
    bool OpenSQL(QString ip, QString userName, QString Passwd, QString dbName, int port);
    void CloseSQL();
    bool IsOpen();
    ///////////////用户账户表/////////////////////////////
    bool CreatAccount();
    bool AddAccount(Account account);
    bool DelAccount(QString username);
    bool ModAccount(Account acc);
    bool GetAccount(QString username, Account &acc);
    bool GetAllAccount(QVector<Account> &data);
    //////////////参数表//////////////////////////////
    bool CreatTableCollectParam();
    bool AddCollectParam(CollectParam param);
    bool DelCollectParam(QString pname);
    bool ModCollectPram(CollectParam param);
    bool GetCollectParam(QString pname, CollectParam &param);
    bool GetAllCollectParam(QVector<CollectParam>&data);
    ////////////数据表////////////////////////
    bool CreatTableCollectData();
    bool AddCollectData(CollectData param);
    bool DelCollectData(QString Pname, QString Dname);
    bool ModCollectData(CollectData param);
    bool GetCollectData(QString pname, QString dname, CollectData &data);
    bool GetAllCollectData(QVector<CollectData>&data);

    QString getCurCmd() const;

private:
    /*! 检查数据库有没有打开
     * \brief checkdb
     * \return
     */
    bool checkdb();
    bool Exec(const QString cmd);
    QSqlQuery QueryExec(const QString cmd,bool &ok);
private:
    QSqlDatabase m_db;
    QString      m_ip;
    QString      m_username;
    QString      m_passwd;
    QString      db_name;
    QString      cur_cmd;
};

#endif // MYSQL_H
