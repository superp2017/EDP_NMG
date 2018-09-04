#ifndef TESTTCP_H
#define TESTTCP_H

#include <QMainWindow>
#include "plccontrol.h"
#pragma execution_character_set("utf-8")
namespace Ui {
class TestTCP;
}

class TestTCP : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestTCP(QWidget *parent = 0);
    ~TestTCP();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_set_pos_clicked();

    void on_pushButton_set_speed_clicked();

    void on_pushButton_query_va_clicked();

    void on_pushButton_start_Ad_clicked();

    void on_pushButton_stop_ad_clicked();

    void on_pushButton_query_speed_clicked();
    void cmd(QString c);
    void on_pushButton_stop_connect_clicked();

    /*! 电机反馈
     * \brief Feedback
     * \param value
     * \param speed true:速度,false:电压
     */
    void Feedback(int value,bool speed);
    /*! AD采样反馈
     * \brief ADFeedback
     * \param data1
     * \param data2
     * \param data3
     */
    void ADFeedback(short data1,short data2,int data3);

private:
    Ui::TestTCP *ui;
    PlcControl control;
};

#endif // TESTTCP_H
