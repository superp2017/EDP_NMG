#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "formcenter.h"
namespace Ui {
class MainWindow;
}
#pragma execution_character_set("utf-8")
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void  closeEvent(QCloseEvent *);

private slots:
    /*! 窗口最小化
     * \brief miniWindow
     */
    void miniWindow();
private:
    Ui::MainWindow *ui;
    FormCenter         center;
};

#endif // MAINWINDOW_H
