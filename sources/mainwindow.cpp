#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitMembers();
    InitConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化数据成员
void MainWindow::InitMembers()
{

}

//关联信号与槽
void MainWindow::InitConnections()
{

}

//打开数据库管理窗口
void MainWindow::openWinDB(const QString &tableName)
{
    //初始化子窗体指针
    pDataBase = new Database;
    //打开新窗口
    pDataBase->setTableName(tableName);
    pDataBase->dbConnect();
    pDataBase->show();

    //关闭子窗口时，打开主窗口（主窗口此前被人为关闭）
    connect(pDataBase,SIGNAL(exitWindows()),this,SLOT(show()));
}

//显示数据库表
void MainWindow::on_pbtnShow_clicked()
{
    //获取下拉菜单的当前选项
    QString table = ui->cmbTable->currentText();
    qDebug() << "table name:" << table;
    //查看数据库表
    openWinDB(table);
}
