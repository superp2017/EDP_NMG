#ifndef SYSCONFIG_H
#define SYSCONFIG_H
#include <QString>
#include "data_global.h"

#pragma execution_character_set("utf-8")
class sysconfig
{
public:
    sysconfig();
    /*! 获取所有配置
     * \brief getConfig
     * \return
     */
    SysSetting getConfig() const;
    /*! 获取数据库配置
     * \brief getDBConfig
     * \return
     */
    DB_Config getDBConfig()const;
    /*! 获取通讯配置
     * \brief getCommunitConfig
     * \return
     */
    CommunitConfig getCommunitConfig()const;

    /*! 获取各个表的创建情况
    * \brief getTableCreat
    * \return
    */
   TableCreat getTableCreat()const;

   /*! 设置所有配置
    * \brief setConfig
    * \param value
    */
    void setConfig(const SysSetting &value);
    /*! 设置数据库的配置
     * \brief setDBConfig
     * \param c
     */
    void setDBConfig(DB_Config c);
    /*! 设置通信系统的配置
     * \brief setCommunitConfig
     * \param c
     */
    void setCommunitConfig(CommunitConfig c);
    /*! 保存表格是否创建
     * \brief setTableConfig
     * \param c
     */
    void setTableConfig(TableCreat c);
private:
    /*! 保存所有配置
     * \brief restore
     */
    void restore();
    SysSetting config;
};

#endif // SYSCONFIG_H
