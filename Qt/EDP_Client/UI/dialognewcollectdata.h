#ifndef DIALOGNEWCOLLECTDATA_H
#define DIALOGNEWCOLLECTDATA_H

#include <QDialog>
#include "data_global.h"
#include "global.h"
namespace Ui {
class DialogNewCollectData;
}

class DialogNewCollectData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewCollectData(QWidget *parent = 0);
    ~DialogNewCollectData();
    void setmodel(DialogShowModel model);
    void setCurData(const CollectData &value);
    CollectData getCurData() const;

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_cancel_clicked();
    void collectParamChange();

private:
    Ui::DialogNewCollectData *ui;
    DialogShowModel     m_model; //当前创建的模式
    CollectData         curData; //当前数据
};

#endif // DIALOGNEWCOLLECTDATA_H
