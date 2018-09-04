#ifndef PLCCONTROL_H
#define PLCCONTROL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "global.h"
#pragma execution_character_set("utf-8")
class PlcControl : public QObject
{
    Q_OBJECT
public:
    PlcControl();
public slots:
    /*! 初始化链接
     * \brief initConnect
     * \return
     */
    bool initConnect(short port);
    /*! 关闭所有连接
     * \brief closeListen
     */
    void closeListen();

    /*! 是否打开或者关闭电机
     * \brief TurnOnOff
     * \param on
     */
    void TurnOnOff(short addr, bool on);
    /*! 发送参数
     * \brief SetParam
     * \param vaule
     * \param speed true:速度，false:位置
     */
    void SetParam(short addr, int vaule, bool speed);
    /*! 查询参数
     * \brief QueryParam
     * \param speed true：速度，false:电压
     */
    void QueryParam(short addr,bool speed);
    /*! 是否启动ad采样
     * \brief TurnOnOffAD
     * \param on
     */
    void TurnOnOffAD(bool on);

signals:
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
    /*! 日志报告
     * \brief cmd
     */
    void cmd(QString);
private slots:
    void sentADCommand(short func);
    void sentCommand(short func, short addr, int data);
    void parseData(QByteArray data);

    /*! 从网络获取数据
     * \brief readDataFromSocket
     */
    void readDataFromSocket();
    /*! 有新链接进来
     * \brief onNewConnection
     */
    void onNewConnection();
    /*! 断开链接
     * \brief onDisConnection
     */
    void onDisConnection();

    /*! 根据ip获取对应的socket
     * \brief getSocket
     * \param IP
     */
    QTcpSocket* getSocket(QString IP);

private:
    QTcpServer *tcpServer;                  //tcpserver
    QMap<QString,QTcpSocket*> socket_list;  //所有的链接的映射
    QTcpSocket *curSocket;                  //当前最后一次的链接
};

#endif // PLCCONTROL_H
