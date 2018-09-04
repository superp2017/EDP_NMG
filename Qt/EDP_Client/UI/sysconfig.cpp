#include "sysconfig.h"
#include <QSettings>
#include "datacenter.h"
sysconfig::sysconfig()
{
    QSettings m_settings("./config.ini",QSettings::IniFormat);
    m_settings.setIniCodec("UTF-8");
    m_settings.beginGroup("MYSQL");
    config.db.server_DB        = m_settings.value("ServerDB").toString();
    config.db.server_username  = m_settings.value("UserName").toString();
    config.db.server_passwd    = m_settings.value("UserPWD").toString();
    config.db.server_ip        = m_settings.value("ServerIP").toString();
    config.db.server_port      = m_settings.value("ServerPort").toString();
    m_settings.endGroup();

    m_settings.beginGroup("Device");
    config.communit.dev.IP     = m_settings.value("Ip").toString();
    config.communit.dev.Port   = m_settings.value("Port").toString();
    m_settings.endGroup();

    m_settings.beginGroup("SerialPort");
    config.communit.serial.bits     = m_settings.value("Bits").toString();
    config.communit.serial.check    = m_settings.value("Check").toString();
    config.communit.serial.com      = m_settings.value("Com").toString();
    config.communit.serial.rate     = m_settings.value("Rate").toString();
    config.communit.serial.stop     = m_settings.value("Stop").toString();
    m_settings.endGroup();
    m_settings.beginGroup("TABLE");
    config.table.IsAccount      = m_settings.value("ACCOUNT").toBool();
    config.table.IsCollectData  = m_settings.value("DATA").toBool();
    config.table.IsCollectParm  = m_settings.value("PARAM").toBool();
    m_settings.endGroup();

    bool isSave = false;
//    if(!config.table.IsAccount){
//        dataCenter::instance()->CreatAccountTable();
//        config.table.IsAccount = true;
//        isSave = true;
//    }
//    if(!config.table.IsCollectData){
//        dataCenter::instance()->CreatCollectDataTable();
//        config.table.IsCollectData = true;
//        isSave = true;
//    }
//    if(!config.table.IsCollectParm){
//        dataCenter::instance()->CreatCollectParamTable();
//        config.table.IsCollectParm = true;
//        isSave = true;
//    }
//    if(isSave)
//        restore();
}

SysSetting sysconfig::getConfig() const
{
    return config;
}

DB_Config sysconfig::getDBConfig() const
{
    return config.db;
}

CommunitConfig sysconfig::getCommunitConfig() const
{
    return config.communit;
}

TableCreat sysconfig::getTableCreat() const
{
    return config.table;
}

void sysconfig::setConfig(const SysSetting &value)
{
    config = value;
    restore();
}

void sysconfig::setDBConfig(DB_Config c)
{
    config.db = c;
    restore();
}

void sysconfig::setCommunitConfig(CommunitConfig c)
{
    config.communit = c;
    restore();
}

void sysconfig::setTableConfig(TableCreat c)
{
    config.table = c;
    restore();
}

void sysconfig::restore()
{
    QSettings m_settings("./config.ini",QSettings::IniFormat);

    m_settings.setIniCodec("UTF-8");

    m_settings.beginGroup("MYSQL");
    m_settings.setValue("ServerDB",config.db.server_DB);
    m_settings.setValue("UserName",config.db.server_username);
    m_settings.setValue("UserPWD",config.db.server_passwd);
    m_settings.setValue("ServerIP", config.db.server_ip);
    m_settings.setValue("ServerPort",config.db.server_port);
    m_settings.endGroup();

    m_settings.beginGroup("Device");
    m_settings.setValue("Ip",config.communit.dev.IP);
    m_settings.setValue("Port",config.communit.dev.Port);
    m_settings.endGroup();

    m_settings.beginGroup("SerialPort");
    m_settings.setValue("Bits",config.communit.serial.bits);
    m_settings.setValue("Check",config.communit.serial.check);
    m_settings.setValue("Com", config.communit.serial.com);
    m_settings.setValue("Rate", config.communit.serial.rate);
    m_settings.setValue("Stop",config.communit.serial.stop);
    m_settings.endGroup();

    m_settings.beginGroup("TABLE");
    m_settings.setValue("ACCOUNT",config.table.IsAccount);
    m_settings.setValue("DATA",config.table.IsCollectData);
    m_settings.setValue("PARAM",config.table.IsCollectParm);
    m_settings.endGroup();

}
