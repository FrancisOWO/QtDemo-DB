#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>

#include <QString>
#include <QVector>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>


namespace Ui {
class Database;
}

class Database : public QWidget
{
    Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    ~Database();

    void closeEvent(QCloseEvent *); //窗口关闭事件

    int dbConnect();
    void setTableName(const QString &name);

signals:
    void exitWindows();         //窗口关闭信号

private:
    Ui::Database *ui;

    QString tableName;
    QString tempConName;
    QVector<QString> conNameVec;

    QSqlTableModel *model;
    QSqlTableModel *modelExcel;

    void InitMembers();         //初始化数据成员
    void InitConnections();     //关联信号与槽

    int exportToExcel(QSqlDatabase &dbExcel);
    int importFromExcel(QSqlDatabase &dbExcel);

private slots:
    void dbAddRec();
    void dbDelRec();
    void dbUndo();
    void dbSave();

    void exportTable();
    void importTable();

};

#endif // DATABASE_H
