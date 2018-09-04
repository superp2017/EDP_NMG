#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>
#include "mysql.h"
#include "sysconfig.h"
#include "data_global.h"
#include <QVector>
#pragma execution_character_set("utf-8")

class dataCenter : public QObject
{
    Q_OBJECT
private:
    explicit dataCenter(QObject *parent = 0);

public:
    static dataCenter* instance(){
        static dataCenter*u =new dataCenter();
        return u;
    }
    /*! 打开数据库
     * \brief OpenSQL
     * \return
     */
    bool OpenSQL();
    /*! 判断数据库是否打开
     * \brief IsOpen
     * \return
     */
    bool IsOpen();
    /*! 关闭数据库
     * \brief CloseSQL
     */
    void CloseSQL();
    /*! 检查数据库是否打开，如果没有，进行一次打开操作
     * \brief CheckSQL
     * \return
     */
    bool CheckSQL();
    /*! 创建账户表
     * \brief CreatAccountTable
     */
    bool CreatAccountTable();
    /*! 登录
     * \brief Login
     * \param name
     * \param pwd
     * \return
     */
    int  Login(QString name,QString pwd);
    /*! 创建CollectParam表
     * \brief CreatCollectParamTabel
     */
    bool CreatCollectParamTable();
    /*! 获取所有采集参数
     * \brief GetAllCollectParam
     * \return
     */
    bool GetAllCollectParam();
    /*! 添加一个采集参数
     * \brief AddCollectParam
     * \param param
     * \return
     */
    bool AddCollectParam(CollectParam param);
    /*! 修改采集参数
     * \brief ModCollectPram
     * \param param
     * \return
     */
    bool ModCollectPram(CollectParam param);
    /*! 删除采集参数
     * \brief DelCollectParam
     * \param pname
     * \return
     */
    bool DelCollectParam(QString pname);
    /*! 创建CollectData表
     * \brief CreatCollectDataTable
     */
    bool CreatCollectDataTable();
    /*! 获取所有的采集数据
     * \brief GetAllCollectData
     * \return
     */
    bool GetAllCollectData();
    /*! 添加一个采集数据
     * \brief AddCollectData
     * \param param
     * \return
     */
    bool AddCollectData(CollectData param);
    /*! 修改采集数据
     * \brief ModCollectData
     * \param param
     * \return
     */
    bool ModCollectData(CollectData param);
    /*! 删除一个采集数据
     * \brief DelCollectData
     * \param Pname
     * \param Dname
     * \return
     */
    bool DelCollectData(QString Pname, QString Dname);

    /*! 获取数据库配置
     * \brief getDBConfig
     * \return
     */
    DB_Config getDBConfig() const;
    /*! 设置数据库配置
     * \brief setDBConfig
     * \param config
     */
    void setDBConfig(const DB_Config &config);
    /*! 获取各个表格是否创建
     * \brief getTableCreat
     * \return
     */
    TableCreat getTableCreat();
    /*! 设置各个表格创建情况
     * \brief setTableCreat
     * \param c
     */
    void setTableCreat(TableCreat &c);
    /*! 获取通讯系统的配置
     * \brief getCommunitConfig
     * \return
     */
    CommunitConfig getCommunitConfig()const;
    /*! 设置通讯配置
     * \brief setCommunitConfig
     * \param c
     */
    void setCommunitConfig(const CommunitConfig &c);
    /*! 返回本地的所有采集参数
     * \brief all_param
     * \return
     */
    QVector<CollectParam> all_param() const;
    /*! 删除某个采集参数
     * \brief removeParam
     * \param index
     */
    void removeParam(int index);
    /*! 修改某个采集参数
     * \brief modifyParam
     * \param p
     * \param index
     */
    void modifyParam(CollectParam p,int index);
    /*! 添加一个采集参数
     * \brief appendParam
     * \param p
     */
    void appendParam(CollectParam p);
    /*! 检查采集参数是否存在
     * \brief checkParamExist
     * \param name
     * \return
     */
    bool checkParamExist(QString name);
    /*! 获取所有的采集数据
     * \brief all_data
     * \return
     */
    QVector<CollectData> all_data() const;
    /*! 移除一条采集数据
     * \brief removeData
     * \param index
     */
    void removeData(int index);
    /*! 修改某条采集数据
     * \brief modifyData
     * \param d
     * \param index
     */
    void modifyData(CollectData d,int index);
    /*! 添加一条采集数据
     * \brief appendData
     * \param d
     */
    void appendData(CollectData d);
private:
    MySql     my_sql;                           //数据库操作句柄
    sysconfig m_config;                         //加载系统的配置
    QVector<CollectParam> m_all_param;          //所有采集参数
    QVector<CollectData>  m_all_data;           //所有采集到的数据
};

#endif // DATACENTER_H
