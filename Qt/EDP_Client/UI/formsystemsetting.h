#ifndef FORMSYSTEMSETTING_H
#define FORMSYSTEMSETTING_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class FormSystemSetting;
}

class FormSystemSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormSystemSetting(QWidget *parent = 0);
    ~FormSystemSetting();

private slots:
    void on_pushButton_mod_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::FormSystemSetting *ui;
};

#endif // FORMSYSTEMSETTING_H
