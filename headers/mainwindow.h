#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Database *pDataBase;

    void InitMembers();         //初始化数据成员
    void InitConnections();     //关联信号与槽

private slots:
    void openWinDB(const QString &tableName);    //打开数据库管理窗口

    void on_pbtnShow_clicked();

    void on_pbtnCompute_clicked();
};
#endif // MAINWINDOW_H
