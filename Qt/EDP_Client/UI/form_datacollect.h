#ifndef FORM_DATACOLLECT_H
#define FORM_DATACOLLECT_H

#include <QWidget>
#include <QTableWidget>
#include "data_global.h"
#include <QStringList>
#include <QShowEvent>

namespace Ui {
class Form_dataCollect;
}
#pragma execution_character_set("utf-8")
class Form_dataCollect : public QWidget
{
    Q_OBJECT

public:
    explicit Form_dataCollect(QWidget *parent = 0);
    ~Form_dataCollect();

private slots:
    void on_pushButton_add_data_clicked();

    void on_pushButton_del_data_clicked();

    void on_pushButton_param_add_clicked();

    void on_pushButton_del_param_clicked();

    void on_pushButton_start_collect_clicked();

    void on_pushButton_stop_collect_clicked();

    void on_pushButton_modify_para_clicked();

    void on_pushButton_modify_data_clicked();

protected:
    /*!  在界面显示前调用，用户数据初始化
     * \brief showEvent
     * \param event
     */
    void showEvent(QShowEvent *event);
private:
    /*! 初始化数据
     * \brief initData
     */
    void initData();
    /*! 初始化表格
     * \brief initTableWidget
     * \param w
     * \param head
     */
    void initTableWidget(QTableWidget *w, QStringList head);
    /*! 添加一条新的参数
     * \brief addNewPara
     * \param param
     */
    void addNewPara(CollectParam param);
    /*! 添加一条新的数据
     * \brief addNewData
     * \param data
     */
    void addNewData(CollectData data);
    /*! 清除参数表的选中状态
     * \brief clearParamSelection
     */\
    void clearParamSelection();
    /*! 清除数据表的选中状态
     * \brief clearDataSelection
     */
    void clearDataSelection();
    /*! 设置数据表的某一行
     * \brief setDataRow
     * \param data
     * \param row
     */
    void setDataRow(CollectData data,int row);
    /*! 设置参数表的某一行
     * \brief setParamRow
     * \param param
     * \param row
     */
    void setParamRow(CollectParam param,int row);


private:
    Ui::Form_dataCollect *ui;
};

#endif // FORM_DATACOLLECT_H
