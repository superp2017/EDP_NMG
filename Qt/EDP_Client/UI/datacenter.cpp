#include "datacenter.h"
#include "data_global.h"
#include <QDebug>
#include <QMessageBox>
dataCenter::dataCenter(QObject *parent) : QObject(parent)
{


}

bool dataCenter::OpenSQL()
{
    return  my_sql.OpenSQL(m_config.getDBConfig().server_ip,\
                           m_config.getDBConfig().server_username,\
                           m_config.getDBConfig().server_passwd,\
                           m_config.getDBConfig().server_DB,\
                           m_config.getDBConfig().server_port.toInt());
}

bool dataCenter::IsOpen()
{
    return  my_sql.IsOpen();
}

void dataCenter::CloseSQL()
{
    if(my_sql.IsOpen()){
        my_sql.CloseSQL();
    }
}

bool dataCenter::CheckSQL()
{
    if(!IsOpen()) {
        if(!OpenSQL()){
            QMessageBox::warning(NULL,"提示","数据库连接失败,请重新连接");
            return false;
        }
        return true;
    }
    return true;
}

bool dataCenter::CreatAccountTable()
{
      if(!CheckSQL()) return false;
      return  my_sql.CreatAccount();
}

int dataCenter::Login(QString name, QString pwd)
{
    if(!CheckSQL()) return -1;

    Account acc;
    if(!my_sql.GetAccount(name,acc)){
        qDebug()<<"获取登录账号失败!";
        return 1;
    }
    if(acc.UserPWD!=pwd){
        qDebug()<<"登录密码不正确!";
        return 2;
    }
    return 0;
}

bool dataCenter::CreatCollectParamTable()
{
    if(!CheckSQL()) return false;
    return  my_sql.CreatTableCollectParam();
}

bool dataCenter::GetAllCollectParam()
{
    if(!CheckSQL()) return false;

    return  my_sql.GetAllCollectParam(m_all_param);
}

bool dataCenter::AddCollectParam(CollectParam param)
{
    if(!CheckSQL()) return false;
    return   my_sql.AddCollectParam(param);
}

bool dataCenter::ModCollectPram(CollectParam param)
{
    if(!CheckSQL()) return false;
    return   my_sql.ModCollectPram(param);
}

bool dataCenter::DelCollectParam(QString pname)
{
    if(!CheckSQL()) return false;
    return my_sql.DelCollectParam(pname);
}

bool dataCenter::CreatCollectDataTable()
{
    if(!CheckSQL()) return false;
    return  my_sql.CreatTableCollectData();
}

bool dataCenter::GetAllCollectData()
{
    if(!CheckSQL()) return false;
    return  my_sql.GetAllCollectData(m_all_data);
}

bool dataCenter::AddCollectData(CollectData param)
{
    if(!CheckSQL()) return false;
    return my_sql.AddCollectData(param);
}

bool dataCenter::ModCollectData(CollectData param)
{
    if(!CheckSQL()) return false;
    return my_sql.ModCollectData(param);
}

bool dataCenter::DelCollectData(QString Pname, QString Dname)
{
    if(!CheckSQL()) return false;
    return my_sql.DelCollectData(Pname,Dname);
}


DB_Config dataCenter::getDBConfig() const
{
    return m_config.getDBConfig();
}


void dataCenter::setDBConfig(const DB_Config &config)
{
    m_config.setDBConfig(config);
}

TableCreat dataCenter::getTableCreat()
{
    return m_config.getTableCreat();
}

void dataCenter::setTableCreat(TableCreat &c)
{
    m_config.setTableConfig(c);
}

CommunitConfig dataCenter::getCommunitConfig() const
{
     return m_config.getCommunitConfig();
}


void dataCenter::setCommunitConfig(const CommunitConfig &c)
{
    m_config.setCommunitConfig(c);
}


QVector<CollectParam> dataCenter::all_param() const
{
    return m_all_param;
}

void dataCenter::removeParam(int index)
{
    m_all_param.removeAt(index);

}

void dataCenter::modifyParam(CollectParam p, int index)
{
    if(m_all_param.count()<=index||index<0) return;
    m_all_param[index] = p;
}

void dataCenter::appendParam(CollectParam p)
{
    m_all_param.push_back(p);
}

bool dataCenter::checkParamExist(QString name)
{
    for(CollectParam p:m_all_param){
        if(p.P_name==name)
            return true;
    }
    return false;
}

QVector<CollectData> dataCenter::all_data() const
{
    return m_all_data;
}

void dataCenter::removeData(int index)
{
    m_all_data.removeAt(index);
}

void dataCenter::modifyData(CollectData d, int index)
{
    if(m_all_data.count()<=index||index<0) return;
    m_all_data[index] = d;
}

void dataCenter::appendData(CollectData d)
{
    m_all_data.push_back(d);
}
