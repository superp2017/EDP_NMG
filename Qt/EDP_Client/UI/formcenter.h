#ifndef FORMCENTER_H
#define FORMCENTER_H

#include <QWidget>
#include "form_home.h"
#include "form_datacollect.h"
#include "formcloudcontrol.h"
#include "formcommunicationsystem.h"
#include "formmovecontrol.h"
#include "formlogin.h"
#include "formsystemsetting.h"

namespace Ui {
class FormCenter;
}

#pragma execution_character_set("utf-8")

class FormCenter : public QWidget
{
    Q_OBJECT

public:
    explicit FormCenter(QWidget *parent = 0);
    ~FormCenter();
signals:
    void systemExit();
    void miniWindow();
private slots:
    void on_pushButton_return_clicked();

    void on_pushButton_setting_clicked();

    void on_pushButton_mini_clicked();

    void on_pushButton_exit_clicked();

    void setCurIndex(int index);

    /*! 检查mysql表格有没有创建
     * \brief checkTable
     */
    void checkTable();
private:
    Ui::FormCenter *ui;
    FormLogin               login;          //登录：索引0
    Form_home               home;           //主页：索引1
    FormMoveControl         move;           //运动控制：索引2
    Form_dataCollect        collect;        //数据采集：索引3
    FormCloudControl        colud;          //云端系统：索引4
    FormCommunicationSystem commutication;  //通讯系统：索引5
    FormSystemSetting       m_setting;      //系统设置：索引6
    int                     m_last_index;   //记录上一次的界面索引
};

#endif // FORMCENTER_H
