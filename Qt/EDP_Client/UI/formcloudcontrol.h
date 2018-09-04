#ifndef FORMCLOUDCONTROL_H
#define FORMCLOUDCONTROL_H

#include <QWidget>
#include <QResizeEvent>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class FormCloudControl;
}

#pragma execution_character_set("utf-8")

struct LightStatus {
    QPushButton* btn;  //按钮
    QLabel *label;     //标签
    bool status;       //状态
};

class FormCloudControl : public QWidget
{
    Q_OBJECT
public:
    explicit FormCloudControl(QWidget *parent = 0);
    ~FormCloudControl();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_select_down_clicked();

    void on_pushButton_select_up_clicked();

    void setButtonSheet(QPushButton*btn);

    void setLightStatus(QLabel *l, bool isopen);

    void onLightClicked();
    void setLight(int index);

private:
    Ui::FormCloudControl *ui;
    QVector<LightStatus>  m_light_Status;  //记录所有灯的按钮、标签和状态
};

#endif // FORMCLOUDCONTROL_H
