#ifndef FORM_HOME_H
#define FORM_HOME_H

#include <QWidget>
namespace Ui {
class Form_home;
}
#pragma execution_character_set("utf-8")
class Form_home : public QWidget
{
    Q_OBJECT

public:
    explicit Form_home(QWidget *parent = 0);
    ~Form_home();
signals:
    void gotoForm(int index);
private slots:
    void on_pushButton_sport_clicked();

    void on_pushButton_data_collect_clicked();

    void on_pushButton_cloud_clicked();

    void on_pushButton_communication_clicked();

private:
    Ui::Form_home *ui;

};

#endif // FORM_HOME_H
