#include "form_datacollect.h"
#include "ui_form_datacollect.h"
#include <QScrollBar>
#include <QDebug>
#include "datacenter.h"
#include "dialognewcollectparam.h"
#include "dialognewcollectdata.h"
#include <QMessageBox>


Form_dataCollect::Form_dataCollect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_dataCollect)
{
    ui->setupUi(this);
    ui->label_collect_title->setPixmap(QPixmap(":/icon/collect_title.png"));

    ui->widget_data->setStyleSheet("#widget_data{border-image: url(:/icon/data_back.png);}");
    ui->widget_param->setStyleSheet("#widget_param{border-image: url(:/icon/data_back.png);}");


    //    ui->widget_data->setStyleSheet("#widget_data{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");
    //    ui->widget_param->setStyleSheet("#widget_param{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");




    ui->pushButton_add_data->setStyleSheet("QPushButton{border-image: url(:/icon/increase.png);}"
                                           "QPushButton:hover{border-image: url(:/icon/increase_down.png);}"
                                           "QPushButton:pressed{border-image: url(:/icon/increase_down.png);}"
                                           "QPushButton:checked{border-image: url(:/icon/increase_down.png);}");
    ui->pushButton_del_data->setStyleSheet("QPushButton{border-image: url(:/icon/delete.png);}"
                                           "QPushButton:hover{border-image: url(:/icon/delete_down.png);}"
                                           "QPushButton:pressed{border-image: url(:/icon/delete_down.png);}"
                                           "QPushButton:checked{border-image: url(:/icon/delete_down.png);}");
    ui->pushButton_modify_data->setStyleSheet("QPushButton{border-image: url(:/icon/modify.png);}"
                                              "QPushButton:hover{border-image: url(:/icon/modify_down.png);}"
                                              "QPushButton:pressed{border-image: url(:/icon/modify_down.png);}"
                                              "QPushButton:checked{border-image: url(:/icon/modify_down.png);}");

    ui->pushButton_param_add->setStyleSheet("QPushButton{border-image: url(:/icon/increase.png);}"
                                            "QPushButton:hover{border-image: url(:/icon/increase_down.png);}"
                                            "QPushButton:pressed{border-image: url(:/icon/increase_down.png);}"
                                            "QPushButton:checked{border-image: url(:/icon/increase_down.png);}");
    ui->pushButton_del_param->setStyleSheet("QPushButton{border-image: url(:/icon/delete.png);}"
                                            "QPushButton:hover{border-image: url(:/icon/delete_down.png);}"
                                            "QPushButton:pressed{border-image: url(:/icon/delete_down.png);}"
                                            "QPushButton:checked{border-image: url(:/icon/delete_down.png);}");
    ui->pushButton_modify_para->setStyleSheet("QPushButton{border-image: url(:/icon/modify.png);}"
                                              "QPushButton:hover{border-image: url(:/icon/modify_down.png);}"
                                              "QPushButton:pressed{border-image: url(:/icon/modify_down.png);}"
                                              "QPushButton:checked{border-image: url(:/icon/modify_down.png);}");


    ui->pushButton_start_collect->setStyleSheet("QPushButton{border-image: url(:/icon/start.png);}"
                                                "QPushButton:hover{border-image: url(:/icon/start_down.png);}"
                                                "QPushButton:pressed{border-image: url(:/icon/start_down.png);}"
                                                "QPushButton:checked{border-image: url(:/icon/start_down.png);}");
    ui->pushButton_stop_collect->setStyleSheet("QPushButton{border-image: url(:/icon/stop.png);}"
                                               "QPushButton:hover{border-image: url(:/icon/stop_down.png);}"
                                               "QPushButton:pressed{border-image: url(:/icon/stop_down.png);}"
                                               "QPushButton:checked{border-image: url(:/icon/stop_down.png);}");

    QStringList header_param;
    header_param<<tr("名称")<<tr("范围")<<tr("单位");
    initTableWidget(ui->tableWidget_param,header_param);

    QStringList header_data;
    header_data<<tr("名称")<<tr("类型")<<tr("数值")<<tr("单位")<<tr("时间");
    initTableWidget(ui->tableWidget_Data,header_data);

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),ui->tableWidget_Data,SLOT(clearSelection()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),ui->tableWidget_param,SLOT(clearSelection()));

    for(int i=0;i<20;++i){
        ui->tableWidget_Data->setRowCount(ui->tableWidget_Data->rowCount()+1);
        CollectData d;
        d.D_name= QString("名称%1").arg(i);
        d.P_name= QString("类型%1").arg(i);
        d.D_value= i*100.0;
        d.D_unit= QString("单位%1").arg(i);
        d.D_time= QString("时间%1").arg(i);
        setDataRow(d,i);
    }

    for(int i=0;i<20;++i){
        ui->tableWidget_param->setRowCount(ui->tableWidget_param->rowCount()+1);
        CollectParam d;
        d.P_name= QString("名称%1").arg(i);
        d.P_unit= QString("单位%1").arg(i);
        d.P_range= QString("范围%1").arg(i);
        ui->comboBox->addItem(d.P_name);
        setParamRow(d,i);
    }
}

Form_dataCollect::~Form_dataCollect()
{
    delete ui;
}

/*!  在界面显示前调用，用户数据初始化
 * \brief showEvent
 * \param event
 */
void Form_dataCollect::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    // initData();
}

void Form_dataCollect::initData()
{
    if(dataCenter::instance()->GetAllCollectParam()){
        for(CollectParam p: dataCenter::instance()->all_param()){
            addNewPara(p);
        }
    }

    if(dataCenter::instance()->GetAllCollectData()){
        for(CollectData d: dataCenter::instance()->all_data()){
            addNewData(d);
        }
    }
}




void Form_dataCollect::on_pushButton_start_collect_clicked()
{
    clearDataSelection();
    clearParamSelection();
}

void Form_dataCollect::on_pushButton_stop_collect_clicked()
{
    clearDataSelection();
    clearParamSelection();
}


void Form_dataCollect::on_pushButton_add_data_clicked()
{
    clearDataSelection();
    DialogNewCollectData data;
    data.setmodel(NEW_Model);
    if(data.exec()==123){
        dataCenter::instance()->appendData(data.getCurData());
        addNewData(data.getCurData());
    }
}

void Form_dataCollect::on_pushButton_modify_data_clicked()
{
    int row = ui->tableWidget_Data->currentRow();
    if(row>=0&&row<ui->tableWidget_Data->rowCount()){
        DialogNewCollectData p;
        p.setmodel(Modify_Model);
        p.setCurData(dataCenter::instance()->all_data().at(row));
        if(p.exec()==123){
            dataCenter::instance()->modifyData(p.getCurData(),row);
            setDataRow(p.getCurData(),row);
        }
    }else{
        QMessageBox::information(this,"提示","请选择需要修改的数据！");
    }
}


void Form_dataCollect::on_pushButton_del_data_clicked()
{
    int row = ui->tableWidget_Data->currentRow();
    if(row>=0&&row<ui->tableWidget_Data->rowCount()){
        DialogNewCollectData p;
        p.setmodel(Del_Model);
        p.setCurData(dataCenter::instance()->all_data().at(row));
        if(p.exec()==123){
            dataCenter::instance()->removeData(row);
            ui->tableWidget_Data->removeRow(row);
        }
    }else{
        QMessageBox::information(this,"提示","请选择需要删除的数据！");
    }
}


void Form_dataCollect::on_pushButton_param_add_clicked()
{
    clearParamSelection();
    DialogNewCollectParam p;
    p.setmodel(NEW_Model);
    if(p.exec()==123){
        dataCenter::instance()->appendParam(p.getCurParam());
        addNewPara(p.getCurParam());
        ui->comboBox->addItem(p.getCurParam().P_name);
    }
}

void Form_dataCollect::on_pushButton_modify_para_clicked()
{
    int row = ui->tableWidget_param->currentRow();
    if(row>=0&&row<ui->tableWidget_param->rowCount()){
        DialogNewCollectParam p;
        p.setmodel(Modify_Model);
        p.setCurParam(dataCenter::instance()->all_param().at(row));
        if(p.exec()==123){
            dataCenter::instance()->modifyParam(p.getCurParam(),row);
            setParamRow(p.getCurParam(),row);
        }
    }else{
        QMessageBox::information(this,"提示","请选择需要修改的参数！");
    }
}


void Form_dataCollect::on_pushButton_del_param_clicked()
{
    int row = ui->tableWidget_param->currentRow();
    if(row>=0&&row<ui->tableWidget_param->rowCount()){
        DialogNewCollectParam p;
        p.setmodel(Del_Model);
        p.setCurParam(dataCenter::instance()->all_param().at(row));
        if(p.exec()==123){
            dataCenter::instance()->removeParam(row);
            ui->tableWidget_param->removeRow(row);
            for(int i=0;i<ui->comboBox->count();++i){
                if(ui->comboBox->itemText(i)==p.getCurParam().P_name){
                    ui->comboBox->removeItem(i);
                    break;
                }
            }
        }
    }else{
        QMessageBox::information(this,"提示","请选择需要删除的参数！");
    }
}


void Form_dataCollect::addNewPara(CollectParam param)
{
    int row = ui->tableWidget_param->rowCount();
    ui->tableWidget_param->setRowCount(row+1);
    setParamRow(param,row);
    ui->comboBox->addItem(param.P_name);
}

void Form_dataCollect::addNewData(CollectData data)
{
    int row = ui->tableWidget_Data->rowCount();
    ui->tableWidget_Data->setRowCount(row+1);
    setDataRow(data,row);
}

void Form_dataCollect::clearParamSelection()
{
    ui->tableWidget_param->clearSelection();
}

void Form_dataCollect::clearDataSelection()
{
    ui->tableWidget_Data->clearSelection();
}


void Form_dataCollect::setParamRow(CollectParam param, int row)
{
    QTableWidgetItem *item0 = ui->tableWidget_param->item(row,0);
    QTableWidgetItem *item1 = ui->tableWidget_param->item(row,1);
    QTableWidgetItem *item2 = ui->tableWidget_param->item(row,2);

    if(item0==NULL){
        item0 = new QTableWidgetItem();
        ui->tableWidget_param->setItem(row,0,item0);
    }
    if(item1==NULL){
        item1 = new QTableWidgetItem();
        ui->tableWidget_param->setItem(row,1,item1);
    }
    if(item2==NULL){
        item2 = new QTableWidgetItem();
        ui->tableWidget_param->setItem(row,2,item2);
    }

    item0->setText(param.P_name);
    item1->setText(param.P_range);
    item2->setText(param.P_unit);

    item0->setForeground(Qt::white);
    item0->setFont(QFont("宋体", 14, QFont::Bold));
    item1->setForeground(Qt::white);
    item1->setFont(QFont("宋体", 14, QFont::Bold));

    item2->setForeground(Qt::white);
    item2->setFont(QFont("宋体", 14, QFont::Bold));

    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
}


/*! 设置数据表格数据
 * \brief Form_dataCollect::setDataRow
 * \param data
 * \param row
 */
void Form_dataCollect::setDataRow(CollectData data,int row)
{
    QTableWidgetItem *item0 = ui->tableWidget_Data->item(row,0);
    QTableWidgetItem *item1 = ui->tableWidget_Data->item(row,1);
    QTableWidgetItem *item2 = ui->tableWidget_Data->item(row,2);
    QTableWidgetItem *item3 = ui->tableWidget_Data->item(row,3);
    QTableWidgetItem *item4 = ui->tableWidget_Data->item(row,4);
    if(item0==NULL){
        item0 = new QTableWidgetItem();
        ui->tableWidget_Data->setItem(row,0,item0);
    }
    if(item1==NULL){
        item1 = new QTableWidgetItem();
        ui->tableWidget_Data->setItem(row,1,item1);
    }
    if(item2==NULL){
        item2 = new QTableWidgetItem();
        ui->tableWidget_Data->setItem(row,2,item2);
    }
    if(item3==NULL){
        item3 = new QTableWidgetItem();
        ui->tableWidget_Data->setItem(row,3,item3);
    }
    if(item4==NULL){
        item4 = new QTableWidgetItem();
        ui->tableWidget_Data->setItem(row,4,item4);
    }

    item0->setText(data.D_name);
    item1->setText(data.P_name);
    item2->setText(QString("%1").arg(data.D_value/100.0));
    item3->setText(data.D_unit);
    item4->setText(data.D_time);

    item0->setForeground(Qt::white);
    item0->setFont(QFont("宋体", 14, QFont::Bold));
    item1->setForeground(Qt::white);
    item1->setFont(QFont("宋体", 14, QFont::Bold));

    item2->setForeground(Qt::white);
    item2->setFont(QFont("宋体", 14, QFont::Bold));

    item3->setForeground(Qt::white);
    item3->setFont(QFont("宋体", 14, QFont::Bold));

    item4->setForeground(Qt::white);
    item4->setFont(QFont("宋体", 14, QFont::Bold));

    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
    item4->setTextAlignment(Qt::AlignCenter);
}

void Form_dataCollect::initTableWidget(QTableWidget *w,QStringList head)
{
    if(w==NULL) return ;
    //设置表头内容
    w->setColumnCount(head.size());
    w->setHorizontalHeaderLabels(head);
    w->setEditTriggers(QTableWidget::NoEditTriggers);//设置不能编辑
    w->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    w->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    w->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽平均
    w->setSortingEnabled(true);//允许列排序
    w->verticalHeader()->hide();//隐藏垂直表头
    w->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(0,0,0,50);font:16pt '宋体';color: white;font: bold};");
    w->horizontalHeader()->setFixedHeight(40);//设置水平表头高度
    w->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    w->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//永久隐藏垂直滚动条
    w->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//永久隐藏水平滚动条
    w->setStyleSheet("background-color:rgba(0,0,0,0);gridline-color : rgb(150, 150, 150);");//设置样式
}











