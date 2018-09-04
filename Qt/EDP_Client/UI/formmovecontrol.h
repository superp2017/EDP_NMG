#ifndef FORMMOVECONTROL_H
#define FORMMOVECONTROL_H

#include <QWidget>
#include <QMovie>
namespace Ui {
class FormMoveControl;
}
#pragma execution_character_set("utf-8")
class FormMoveControl : public QWidget
{
    Q_OBJECT

public:
    explicit FormMoveControl(QWidget *parent = 0);
    ~FormMoveControl();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::FormMoveControl *ui;
    QMovie *movie;       //用户加载gif动画
};

#endif // FORMMOVECONTROL_H
