#ifndef FORMCOMMUNICATIONSYSTEM_H
#define FORMCOMMUNICATIONSYSTEM_H

#include <QWidget>
#include "data_global.h"
namespace Ui {
class FormCommunicationSystem;
}
#pragma execution_character_set("utf-8")


class FormCommunicationSystem : public QWidget
{
    Q_OBJECT

public:
    explicit FormCommunicationSystem(QWidget *parent = 0);
    ~FormCommunicationSystem();

private slots:
    void on_pushButton_dev_ok_clicked();
    void on_pushButton_bus_ok_clicked();
private:
    /*! 初始化界面
     * \brief initCOM
     */
    void initCOM();
    /*! 初始化本地配置
     * \brief initConfig
     */
    void initConfig();
private:
    Ui::FormCommunicationSystem *ui;
    CommunitConfig config;      //本地通讯配置
};

#endif // FORMCOMMUNICATIONSYSTEM_H
