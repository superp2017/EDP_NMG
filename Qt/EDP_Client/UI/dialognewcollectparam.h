#ifndef DIALOGNEWCOLLECTPARAM_H
#define DIALOGNEWCOLLECTPARAM_H

#include <QDialog>
#include "data_global.h"
#include "global.h"
namespace Ui {
class DialogNewCollectParam;
}

class DialogNewCollectParam : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewCollectParam(QWidget *parent = 0);
    ~DialogNewCollectParam();

    CollectParam getCurParam() const;
    void setCurParam(const CollectParam &value);
    void setmodel(DialogShowModel model);
private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::DialogNewCollectParam *ui;
    CollectParam curParam;  //当前的参数
    DialogShowModel m_model; //当前的模式
};

#endif // DIALOGNEWCOLLECTPARAM_H
