#include "formmovecontrol.h"
#include "ui_formmovecontrol.h"
#include <QToolTip>
#include <QDoubleValidator>

FormMoveControl::FormMoveControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMoveControl)
{
    ui->setupUi(this);

    ui->label_move_title->setPixmap(QPixmap(":/icon/move_title.png"));

    ui->widget_left->setStyleSheet("#widget_left{border-image: url(:/icon/move_left_back.png);}");
    ui->widget_right->setStyleSheet("#widget_right{border-image: url(:/icon/move_right_back.png);}");

//    ui->widget_left->setStyleSheet("#widget_left{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");
//    ui->widget_right->setStyleSheet("#widget_right{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");



    ui->pushButton_ok->setStyleSheet("QPushButton{border-image: url(:/icon/ok.png);}"
                                     "QPushButton:hover{border-image: url(:/icon/ok_down.png);}"
                                     "QPushButton:pressed{border-image: url(:/icon/ok_down.png);}"
                                     "QPushButton:checked{border-image: url(:/icon/ok_down.png);}");

    ui->pushButton_reset->setStyleSheet("QPushButton{border-image: url(:/icon/reset.png);}"
                                        "QPushButton:hover{border-image: url(:/icon/reset_down.png);}"
                                        "QPushButton:pressed{border-image: url(:/icon/reset_down.png);}"
                                        "QPushButton:checked{border-image: url(:/icon/reset_down.png);}");


    QDoubleValidator *d = new QDoubleValidator(-9999999.00,9999999.99,2);
    ui->lineEdit_x_default_pos->setValidator(d);
    ui->lineEdit_x_real_pos->setValidator(d);
    ui->lineEdit_x_speed->setValidator(d);
    ui->lineEdit_y_default_pos->setValidator(d);
    ui->lineEdit_y_real_pos->setValidator(d);
    ui->lineEdit_y_spreed->setValidator(d);

    //加载gif图片
    movie = new QMovie(":/icon/move.gif");
    movie->setScaledSize(ui->label_move->size());

    ui->label_move->setMovie(movie);
    connect(movie,SIGNAL(finished()),movie,SLOT(start()));
    movie->start();
}

FormMoveControl::~FormMoveControl()
{
    delete ui;
}



void FormMoveControl::on_pushButton_ok_clicked()
{
    QString  x_de_pos   =  ui->lineEdit_x_default_pos->text().trimmed();
    QString  y_de_pos   =  ui->lineEdit_y_default_pos->text().trimmed();
    QString  x_real_pos =  ui->lineEdit_x_real_pos->text().trimmed();
    QString  y_real_pos =  ui->lineEdit_y_real_pos->text().trimmed();
    QString  x_speed    =  ui->lineEdit_x_speed->text().trimmed();
    QString  y_speed    =  ui->lineEdit_y_spreed->text().trimmed();
    if(x_de_pos.isEmpty()){
        QToolTip::showText(ui->lineEdit_x_default_pos->mapToGlobal(QPoint(100, 0)), "X轴给定不能为空!");
        return;
    }
    if(y_de_pos.isEmpty()){
        QToolTip::showText(ui->lineEdit_y_default_pos->mapToGlobal(QPoint(100, 0)), "Y轴给定不能为空!");
        return;
    }
    if(x_real_pos.isEmpty()){
        QToolTip::showText(ui->lineEdit_x_real_pos->mapToGlobal(QPoint(100, 0)), "X轴实际位置不能为空！");
        return;
    }
    if(y_real_pos.isEmpty()){
        QToolTip::showText(ui->lineEdit_y_real_pos->mapToGlobal(QPoint(100, 0)), "Y轴实际位置不能为空！");
        return;
    }
    if(x_speed.isEmpty()){
        QToolTip::showText(ui->lineEdit_x_speed->mapToGlobal(QPoint(100, 0)), "X轴速度不能为空！");
        return;
    }
    if(y_speed.isEmpty()){
        QToolTip::showText(ui->lineEdit_y_spreed->mapToGlobal(QPoint(100, 0)), "Y轴速度不能为空！");
        return;
    }


}

void FormMoveControl::on_pushButton_reset_clicked()
{
    ui->lineEdit_x_default_pos->clear();
    ui->lineEdit_x_real_pos->clear();
    ui->lineEdit_x_speed->clear();
    ui->lineEdit_y_default_pos->clear();
    ui->lineEdit_y_real_pos->clear();
    ui->lineEdit_y_spreed->clear();
}


