#ifndef DATA_GLOBAL_H
#define DATA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATA_LIBRARY)
#  define DATASHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATASHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QString>
#pragma execution_character_set("utf-8")


struct CollectParam {
    QString P_name;   //参数名称
    QString P_range;  //参数范围
    QString P_unit;   //参数单位
};//采集参数

struct CollectData {
    QString D_name;  //名称
    QString P_name;  //所属参数
    int     D_value; //数值
    QString D_unit;   //参数单位
    QString D_time;  //创建时间
};//采集的数据

struct Account{
    QString UserName;//登录名
    QString UserPWD;//登录密码
};


struct DB_Config{
    QString server_DB;//数据库名称
    QString server_username; //数据库用户名
    QString server_passwd;//数据库密码
    QString server_ip;//数据库ip
    QString server_port;//数据库端口
};//数据库系统设置

struct Dev_Config{
    QString IP;
    QString Port;
};//硬件配置

struct SerialPortConfig{
    QString com;//com
    QString bits;//数据位
    QString stop;//停止位
    QString check;//校验
    QString rate;//波特率
};

struct CommunitConfig{
    Dev_Config dev;
    SerialPortConfig serial;
};//通讯系统配置

struct TableCreat{
   bool IsAccount;      //是否创建Accont表
   bool IsCollectParm; //是否创建CollectParm表
   bool IsCollectData; //是否创建CollectData表
};//保存系统是否创建数据库表

struct SysSetting{
    DB_Config db;
    CommunitConfig communit;
    TableCreat  table;
};//系统设置




#endif // DATA_GLOBAL_H
