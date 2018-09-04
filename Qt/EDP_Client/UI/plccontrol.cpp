#include "plccontrol.h"
#include <QDebug>
#include "iostream"
const int MaxSIZE = 8;
const int MaxSIZE_AD = 10;

PlcControl::PlcControl()
{
    tcpServer = new QTcpServer();
}

bool PlcControl::initConnect(short port)
{
    if(tcpServer!=NULL && tcpServer->listen(QHostAddress::AnyIPv4,port))
    {
        connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
        return true;
    }
    return false;
}

void PlcControl::closeListen()
{
    if(tcpServer!=NULL){
        QList<QString>  keys= socket_list.keys();
        for(int i=0;i< keys.size();i++){
            if(socket_list[keys[i]]!=NULL){
                socket_list[keys[i]]->close();
            }
        }
        socket_list.clear();
        disconnect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
        tcpServer->close();
        curSocket = NULL;
    }
}


void PlcControl::TurnOnOff(short addr, bool on)
{
    short func = on?1:2;
    sentCommand(func,addr,0);
}

void PlcControl::SetParam(short addr,int vaule, bool speed)
{
    short func = speed?4:3;
    sentCommand(func,addr,vaule);
}

void PlcControl::QueryParam(short addr,bool speed)
{
    short func = speed?5:6;
    sentCommand(func,addr,0);
}

void PlcControl::TurnOnOffAD(bool on)
{
    short func = on?7:8;
    sentADCommand(func);
}


void PlcControl::sentCommand(short func,short addr,int data)
{

    if(curSocket!=NULL&&curSocket->state()!=0)
    {
        char buf[MaxSIZE]={0};
        buf[0] = 0;
        buf[1] = func;
        buf[2] = 0;
        buf[3] = addr;
        //    memcpy(&buf[0],&func,2);
        //    memcpy(&buf[2],&addr,2);
        memcpy(&buf[4],&data,4);
        QByteArray array = QByteArray(buf,MaxSIZE);
        QByteArray sss = array.toHex();
        QString sendStr;
        for(int i=0;i<sss.size();i++){
            sendStr.append(sss.at(i));
        }
        emit cmd("发送指令:"+sendStr);
        curSocket->write(buf,MaxSIZE);
        curSocket->flush();
    }else{
        emit cmd("设备未连接！");
    }
}

void PlcControl::sentADCommand(short func)
{
    if(curSocket!=NULL&&curSocket->state()!=0)
    {
        char buf[MaxSIZE_AD]={0};
        buf[0] = 0;
        buf[1] = func;
        QByteArray array = QByteArray(buf,MaxSIZE_AD);
        QByteArray sss = array.toHex();
        QString sendStr;
        for(int i=0;i<sss.size();i++){
            sendStr.append(sss.at(i));
        }
        emit cmd("发送AD指令:"+sendStr);
        curSocket->write(buf,MaxSIZE_AD);
        curSocket->flush();
    }else{
        emit cmd("设备未连接！");
    }
}


void PlcControl::parseData(QByteArray data)
{
    if(data.size()!=MaxSIZE&&data.size()!=MaxSIZE_AD){
        emit cmd("解析失败，指令长度不满足！");
        return ;
    }
    short func;
    memcpy(&func,&data[0],2);
    if(func==17){
        if(data.size()==MaxSIZE_AD){
            short data1,data2;
            int data3;
            memcpy(&data1,&data[2],2);
            memcpy(&data2,&data[4],2);
            memcpy(&data3,&data[0],4);
            emit  ADFeedback(data1,data2,data3);
        }else{
            emit cmd("解析失败AD指令长度不等于17！");
            return ;
        }
    }else
    {
        if(data.size()==MaxSIZE_AD){
            short addr;
            int value;
            memcpy(&addr,&data[2],2);
            memcpy(&value,&data[4],4);
            emit Feedback(value,func==15);
        }else{
            emit cmd("解析失败控制指令长度不等于15！");
            return ;
        }
    }
}

void PlcControl::readDataFromSocket()
{
    QTcpSocket * socket =static_cast<QTcpSocket*>(sender());
    if(socket!=NULL&&socket->state()!=0){
        QByteArray rawreply= socket->readAll();
        QString retString="";
        QByteArray hex = rawreply.toHex();
        for(int i=0;i<hex.size();i++){
            retString.append(hex.at(i));
        }
        emit cmd("收到指令:"+retString);
        parseData(rawreply);
    }
}

void PlcControl::onNewConnection()
{
    if(tcpServer==NULL) return;
    QTcpSocket *newpeer= tcpServer->nextPendingConnection();
    QString ip = newpeer->peerAddress().toString();
    socket_list[ip] = newpeer;
    curSocket = newpeer;
    connect(newpeer,SIGNAL(readyRead()),this,SLOT(readDataFromSocket()));
    connect(newpeer,SIGNAL(disconnected()),this,SLOT(onDisConnection()));
    newpeer->flush();
    emit cmd("有新的链接IP:"+ip);
}

void PlcControl::onDisConnection()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    socket_list.remove(client->peerAddress().toString());
    emit cmd("IP:"+client->peerAddress().toString()+"断开链接");
    curSocket = NULL;
}

QTcpSocket *PlcControl::getSocket(QString IP)
{
    if(IP.isEmpty()) {
        qDebug()<<"IP is empty";
        emit cmd("IP is empty");
        return NULL;
    }
    if(!socket_list.contains(IP)){
        qDebug()<<"没有链接,IP:"<<IP;
        emit cmd("没有链接,IP:"+IP);
        return NULL;
    }
    QTcpSocket *socket = socket_list[IP];
    if(socket!=NULL&&socket->state()!=0)
    {
        return  socket;
    }
    qDebug()<<"链接不存在或者已经断开";
    emit cmd("链接不存在或者已经断开");
    return NULL;
}
