#include "dialognewcollectparam.h"
#include "ui_dialognewcollectparam.h"
#include <QToolTip>
#include "datacenter.h"
#include <QMessageBox>
DialogNewCollectParam::DialogNewCollectParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewCollectParam)
{
    ui->setupUi(this);
    setStyleSheet("#DialogNewCollectParam{border-image: url(icon/cloud_right_back.png);}");

//    setStyleSheet("#DialogNewCollectParam{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");

    ui->pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/cancel.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/cancel_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/cancel_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/cancel_down.png);}");
    setWindowFlags(Qt::Window|\
                   Qt::FramelessWindowHint |\
                   Qt::WindowSystemMenuHint|\
                   Qt::WindowMinimizeButtonHint|\
                   Qt::WindowMaximizeButtonHint);
    m_model = NEW_Model;
}

DialogNewCollectParam::~DialogNewCollectParam()
{
    delete ui;
}

void DialogNewCollectParam::on_pushButton_add_clicked()
{
    if(m_model==NEW_Model||m_model==Modify_Model){
        curParam.P_name  = ui->lineEdit_pname->text().trimmed();
        curParam.P_range = ui->lineEdit_prange->text().trimmed();
        curParam.P_unit  = ui->lineEdit_punit->text().trimmed();
        if( curParam.P_name.isEmpty()){
            QToolTip::showText(ui->lineEdit_pname->mapToGlobal(QPoint(100, 0)), "名称不能为空!");
            return;
        }
        if( curParam.P_range.isEmpty()){
            QToolTip::showText(ui->lineEdit_prange->mapToGlobal(QPoint(100, 0)), "范围不能为空!");
            return;
        }
        if(curParam.P_unit.isEmpty()){
            QToolTip::showText(ui->lineEdit_punit->mapToGlobal(QPoint(100, 0)), "单位不能为空！");
            return;
        }
        if(m_model==NEW_Model){
            if(dataCenter::instance()->checkParamExist(curParam.P_name)){
                QToolTip::showText(ui->lineEdit_pname->mapToGlobal(QPoint(100, 0)), "该名称已经存在!");
                return;
            }
            if(dataCenter::instance()->AddCollectParam(curParam)){
                done(123);
            }else{
                QMessageBox::warning(this,"提示","创建失败！");
                return;
            }
        }else{
            if(dataCenter::instance()->ModCollectPram(curParam)){
                done(123);
            }else{
                QMessageBox::warning(this,"提示","修改失败！");
                return;
            }
        }
    }

    if(m_model==Del_Model){
        if(dataCenter::instance()->DelCollectParam(curParam.P_name)){
            done(123);
        }else{
            QMessageBox::warning(this,"提示","删除失败");
            done(-1);
            return;
        }
    }
}

void DialogNewCollectParam::on_pushButton_cancel_clicked()
{
    done(-1);
}


void DialogNewCollectParam::setCurParam(const CollectParam &value)
{
    curParam = value;
    ui->lineEdit_pname->setText(value.P_name);
    ui->lineEdit_prange->setText(value.P_range);
    ui->lineEdit_punit->setText(value.P_unit);
}

void DialogNewCollectParam::setmodel(DialogShowModel model)
{
    m_model = model;
    if(m_model==NEW_Model){
        ui->lineEdit_pname->setText("");
        ui->lineEdit_prange->setText("");
        ui->lineEdit_punit->setText("");
        curParam.P_name="";
        curParam.P_range="";
        curParam.P_unit="";
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/increase.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/increase_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/increase_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/increase_down.png);}");
    }
    if(m_model==Del_Model){
        ui->lineEdit_pname->setEnabled(false);
        ui->lineEdit_prange->setEnabled(false);
        ui->lineEdit_punit->setEnabled(false);
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/delete.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/delete_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/delete_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/delete_down.png);}");
    }
    if(m_model==Modify_Model){
        ui->lineEdit_pname->setEnabled(false);
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/modify.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/modify_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/modify_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/modify_down.png);}");
    }
}


CollectParam DialogNewCollectParam::getCurParam() const
{
    return curParam;
}

