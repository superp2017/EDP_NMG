#include "mysql.h"
#include <QDebug>

MySql::MySql()
{

}


/*! 创建参数表
 * \brief MySql::CreatTableCollectParam
 * \return
 */
bool MySql::CreatTableCollectParam()
{
    QString cmd= "create table if not exists collectparam(\
            P_name varchar(12) not null primary key,\
            P_range varchar(12) not null,\
            P_unit varchar(4) not null) DEFAULT CHARSET utf8 COLLATE utf8_general_ci";
            return Exec(cmd) ;
}

/*! 创建表
 * \brief MySql::CreatTableCollectData
 * \return
 */
bool MySql::CreatTableCollectData()
{
    QString cmd= "create table if not exists collectdata(\
            D_name  varchar(12) not null,\
            P_name  varchar(12) not null,\
            D_unit  varchar(4) not null,\
            D_value int not null default 0,\
            D_time  varchar(25) not null,\
            primary key(D_name,P_name),\
            foreign key (P_name) references collectparam(P_name))\
            DEFAULT CHARSET utf8 COLLATE utf8_general_ci";
            return Exec(cmd) ;
}

/*!  增加一条采集参数
 * \brief AddCollectParam
 * \param param
 */
bool MySql::AddCollectParam(CollectParam param)
{
    if(!checkdb()) return false;
    QString cmd= QString("insert into collectparam(P_name,P_range,P_unit) values('%1','%2','%3')")\
            .arg(param.P_name).arg(param.P_range).arg(param.P_unit);
    return Exec(cmd);
}

/*! 删除一条采集参数
 * \brief MySql::DelCollectParam
 * \param PID
 */
bool MySql::DelCollectParam(QString pname)
{
    QString cmd=QString("delete from collectparam where P_name = '%1'").arg(pname) ;
    return Exec(cmd);
}

/*! 修改采集参数
 * \brief MySql::ModCollectPram
 * \param param
 */
bool MySql::ModCollectPram(CollectParam param)
{
    QString cmd = QString("UPDATE collectparam set P_range = '%1', P_unit = '%2' where P_name= '%3'")\
            .arg(param.P_range).arg(param.P_unit).arg(param.P_name);
    return Exec(cmd);
}

/*! 获取单个采集参数
 * \brief MySql::GetCollectParam
 * \param PID
 * \return
 */
bool MySql::GetCollectParam(QString pname,CollectParam &param)
{
    QString cmd = QString("select * from  collectparam where P_name = '%1'").arg(pname);
    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetCollectParam query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    if(m_query.next()){
        // 获取当前记录中某一列的值
        int index_name      = rec.indexOf("P_name");
        int index_range     = rec.indexOf("P_range");
        int index_unit      = rec.indexOf("P_unit");
        if(index_name>=0)
            param.P_name    = m_query.value(index_name).toString();
        if(index_range>=0)
            param.P_range   = m_query.value(index_range).toString();
        if(index_unit>=0)
            param.P_unit    = m_query.value(index_unit).toString();
    }
    return true;
}

/*! 获取所有的采集参数
 * \brief MySql::GetAllCollectParam
 * \return
 */
bool  MySql::GetAllCollectParam(QVector<CollectParam> &data)
{
    QString cmd = QString("select * from  collectparam");
    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetAllCollectParam query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    while(m_query.next())
    {
        rec = m_query.record();
        CollectParam param;
        // 获取当前记录中某一列的值
        int index_name      = rec.indexOf("P_name");
        int index_range     = rec.indexOf("P_range");
        int index_unit      = rec.indexOf("P_unit");
        if(index_name>=0)
            param.P_name        = m_query.value(index_name).toString();
        if(index_range>=0)
            param.P_range       = m_query.value(index_range).toString();
        if(index_unit>=0)
            param.P_unit        = m_query.value(index_unit).toString();
        data.push_back(param);
    }
    return true;
}



/*! 增加一个采集的数据
 * \brief MySql::AddCollectData
 * \param param
 */
bool MySql::AddCollectData(CollectData param)
{
    if(!checkdb()) return false;
    QString cmd= QString("insert into collectdata(D_name,P_name,D_unit,D_value,D_time) values('%1','%2','%3',%4,'%5')")\
            .arg(param.D_name).arg(param.P_name).arg(param.D_unit).arg(param.D_value).arg(param.D_time);
    return Exec(cmd);
}

/*! 删除一条采集的数据
 * \brief MySql::DelCollectData
 * \param PID
 */
bool MySql::DelCollectData(QString Pname,QString Dname)
{
    QString cmd = QString("delete from collectdata where P_name = '%1' && D_name= '%2'").arg(Pname).arg(Dname) ;
    return Exec(cmd);
}

/*! 修改采集数据
 * \brief MySql::ModCollectData
 * \param param
 */
bool MySql::ModCollectData(CollectData param)
{    
    QString cmd = QString("UPDATE collectdata \
                          set D_name = '%1', P_name = '%2', D_value= %3,D_unit= '%4'\
            where P_name= '%5' && D_name = '%6'")\
            .arg(param.D_name)
            .arg(param.P_name)
            .arg(param.D_value)
            .arg(param.D_unit)
            .arg(param.P_name)
            .arg(param.D_name);
            return Exec(cmd);
}

/*! 获取单个采集数据
 * \brief MySql::GetCollectData
 * \param PID
 * \return
 */
bool MySql::GetCollectData(QString pname,QString dname,CollectData &data)
{
    QString cmd = QString("select * from  collectdata where P_name = '%1' && D_name = '%2'").arg(pname).arg(dname);
    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetCollectData query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    if(m_query.next()){
        // 获取当前记录中某一列的值
        int index_dname     = rec.indexOf("D_name");
        int index_pname     = rec.indexOf("P_name");
        int index_dvalue    = rec.indexOf("D_value");
        int index_dunit      = rec.indexOf("D_unit");
        int index_dtime      = rec.indexOf("D_time");
        if(index_dname>=0)
            data.D_name    = m_query.value(index_dname).toString();
        if(index_pname>=0)
            data.P_name   = m_query.value(index_pname).toString();
        if(index_dvalue>=0)
            data.D_value    = m_query.value(index_dvalue).toInt();
        if(index_dunit>=0)
            data.D_unit    = m_query.value(index_dunit).toString();
        if(index_dtime>=0)
            data.D_time    = m_query.value(index_dtime).toString();
    }
    return true;
}

/*! 获取所有的采集数据
 * \brief MySql::GetAllCollectData
 * \return
 */
bool MySql::GetAllCollectData(QVector<CollectData> &data)
{
    QString cmd = QString("select * from  collectdata");
    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetAllCollectData query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    while(m_query.next())
    {
        rec = m_query.record();
        CollectData param;
        // 获取当前记录中某一列的值
        int index_dname     = rec.indexOf("D_name");
        int index_pname     = rec.indexOf("P_name");
        int index_dvalue    = rec.indexOf("D_value");
        int index_dunit      = rec.indexOf("D_unit");
        int index_dtime      = rec.indexOf("D_time");
        if(index_dname>=0)
            param.D_name    = m_query.value(index_dname).toString();
        if(index_pname>=0)
            param.P_name   = m_query.value(index_pname).toString();
        if(index_dvalue>=0)
            param.D_value    = m_query.value(index_dvalue).toInt();
        if(index_dunit>=0)
            param.D_unit    = m_query.value(index_dunit).toString();
        if(index_dtime>=0)
            param.D_time    = m_query.value(index_dtime).toString();
        data.push_back(param);
    }
    return true;
}

bool MySql::checkdb()
{
    if(!m_db.isOpen()){
        return m_db.open();
    }
    return true;
}

bool MySql::OpenSQL(QString ip, QString userName, QString Passwd, QString dbName,int port)
{
    m_ip       = ip;
    m_username = userName;
    m_passwd   = Passwd;
    db_name    = dbName;

    m_db = QSqlDatabase::addDatabase("QMYSQL"); //QMYSQL代表是MYSQL数据库
    m_db.setHostName(ip);           //数据库地址
    m_db.setUserName(userName);     //用户名称
    m_db.setPassword(Passwd);       //用户密码
    m_db.setPort(port);
    m_db.setDatabaseName(dbName);  //数据库名称
    if(m_db.open())
    {
        qDebug() << dbName+":打开成功!";
        m_db.exec("set names utf8");
        return true;
    }
    qDebug() << dbName+":打开失败!";
    return false;
}

void MySql::CloseSQL()
{
    if(m_db.isOpen()){
        m_db.close();
    }
}

bool MySql::IsOpen()
{
    return m_db.isOpen();
}

/*! 创建用户账户表
 * \brief MySql::CreatAccount
 * \return
 */
bool MySql::CreatAccount()
{
    QString cmd= "create table if not exists account(\
            username varchar(12) not null primary key,\
            userpwd varchar(12) not null) DEFAULT CHARSET utf8 COLLATE utf8_general_ci";
            return Exec(cmd) ;
}

/*! 增加一条账户
 * \brief MySql::AddAccount
 * \return
 */
bool MySql::AddAccount(Account account)
{
    if(!checkdb()) return false;
    QString cmd= QString("insert into account(username,userpwd) values('%1','%2')")\
            .arg(account.UserName).arg(account.UserPWD);
    return Exec(cmd);
}

/*! 删除一个账户
 * \brief MySql::DelAccount
 * \return
 */
bool MySql::DelAccount(QString username)
{
    QString cmd=QString("delete from account where username = '%1'").arg(username);
    return Exec(cmd);
}

/*! 修改账户密码
 * \brief MySql::ModAccount
 * \return
 */
bool MySql::ModAccount(Account acc)
{
    QString cmd = QString("UPDATE account set userpwd = '%1' where username= '%2'")\
            .arg(acc.UserPWD).arg(acc.UserName);
    return Exec(cmd);
}

/*! 获取账户信息
 * \brief MySql::GetAccount
 * \return
 */
bool MySql::GetAccount(QString username,Account&acc)
{
    QString cmd = QString("select * from  account where username = '%1'").arg(username);

    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetAccount query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    if(m_query.next()){
        // 获取当前记录中某一列的值
        int index_name      = rec.indexOf("username");
        int index_pwd     = rec.indexOf("userpwd");
        if(index_name>=0)
            acc.UserName  = m_query.value(index_name).toString();
        if(index_pwd>=0)
            acc.UserPWD   = m_query.value(index_pwd).toString();
    }
    return true;
}

/*! 获取所有账户信息
 * \brief MySql::GetAllAccount
 * \return
 */
bool MySql::GetAllAccount(QVector<Account> &data)
{
    QString cmd = QString("select * from  account");
    bool ok;
    QSqlQuery m_query= QueryExec(cmd,ok);
    if(!ok){
        return false;
    }
    if (m_query.size()==0){
        qDebug()<<"GetAllAccount query result is empty!";
        return false;
    }
    QSqlRecord rec = m_query.record();
    while(m_query.next())
    {
        rec = m_query.record();
        Account acc;
        // 获取当前记录中某一列的值
        int index_name    = rec.indexOf("username");
        int index_pwd     = rec.indexOf("userpwd");
        if(index_name>=0)
            acc.UserName  = m_query.value(index_name).toString();
        if(index_pwd>=0)
            acc.UserPWD   = m_query.value(index_pwd).toString();
        data.push_back(acc);
    }
    return true;
}

bool MySql::Exec(const QString cmd)
{
    qDebug()<<cmd;
    cur_cmd = cmd;
    QSqlQuery   m_query(m_db);
    bool success = m_query.exec(cmd);
    if(!success){
        qDebug() << "执行失败";
        return false;
    }
    qDebug() << "执行成功";
    return true;
}

QSqlQuery MySql::QueryExec(const QString cmd,bool &ok)
{
    qDebug()<<cmd;
    cur_cmd = cmd;
    QSqlQuery  m_query(m_db);
    bool success = m_query.exec(cmd);
    if(!success){
        qDebug() << "查询失败";
        ok = false;
    }else{
        qDebug() << "查询成功";
        ok = true;
        m_query.seek(-1);
    }
    return m_query;
}

QString MySql::getCurCmd() const
{
    return cur_cmd;
}

