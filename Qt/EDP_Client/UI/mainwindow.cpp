#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include "datacenter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet("#MainWindow{border-image: url(:/icon/ui-back.jpg);}");


    setWindowFlags(Qt::Window|\
                   Qt::FramelessWindowHint |\
                   Qt::WindowSystemMenuHint|\
                   Qt::WindowMinimizeButtonHint|\
                   Qt::WindowMaximizeButtonHint);

    setCentralWidget(&center);

    connect(&center,SIGNAL(miniWindow()),this,SLOT(miniWindow()));
    connect(&center,SIGNAL(systemExit()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::miniWindow()
{
    this->showMinimized();
}


void MainWindow::closeEvent(QCloseEvent *)
{
    //退出系统
    QApplication::quit();
}
