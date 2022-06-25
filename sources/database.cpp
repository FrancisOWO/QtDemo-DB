#include "database.h"
#include "ui_database.h"

#include <QDebug>

Database::Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);
}

Database::~Database()
{
    delete ui;
}

void Database::closeEvent(QCloseEvent *)
{
    emit exitWindows();
}

//初始化数据成员
void Database::InitMembers()
{

}

//关联信号与槽
void Database::InitConnections()
{

}

//连接数据库
int Database::dbConnect()
{
    //("QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7")
    //用连接名识别连接，防止新连接覆盖旧连接，导致各模块无法同时访问数据库
    QSqlDatabase db;
    //连接已存在则直接打开数据库，否则新建连接
    if(QSqlDatabase::contains(tempConName))
        db = QSqlDatabase::database(tempConName);
    else {
        db = QSqlDatabase::addDatabase("QMYSQL", tempConName);
        conNameVec.append(tempConName);
    }
    //设置数据库
    db.setHostName("localhost");    //主机名，本地：localhost或127.0.0.1
    db.setPort(3306);               //端口
    db.setUserName("root");         //登录用户名
    db.setPassword("12345abc_");    //登录密码
    db.setDatabaseName("demo");     //数据库名
    //打开数据库
    if(db.open() == false) {
        //打开失败，弹窗错误信息
        QMessageBox::warning(this, "warning", db.lastError().text());
        return -1;
    }

    //注意：addDatabase使用连接名参数后，query和model初始化都要指定db!!!
    //测试数据库连接是否正确，查询当前数据库名
    //select database();
    QSqlQuery query("select database();", db);
    qDebug() << "select database();";
    while(query.next())
        qDebug() << query.value(0).toString();
    qDebug() << "tables:" << db.tables();

    model = new QSqlTableModel(this, db);   //获取数据库模型
    ui->tblShow->setModel(model);           //绑定数据库模型到Qt表
    model->setTable(tableName);             //选择数据库表
    model->select();                        //查询数据库表

    //数据更新方式：手动提交
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //隐藏不需要显示的列
    ui->tblShow->setColumnHidden(0,true);

    return 0;
}

//设置表名
void Database::setTableName(const QString &name)
{
    tableName = name;
    //ui中的表名
    ui->ptxtTableName->setPlainText(name);
}

//把数据库表导出到excel
int Database::exportToExcel(QSqlDatabase &dbExcel)
{
    return 0;
}

//从excel导入数据库表
int Database::importFromExcel(QSqlDatabase &dbExcel)
{
    return 0;
}

//添加记录
void Database::dbAddRec()
{

}

//删除记录
void Database::dbDelRec()
{

}

//撤销修改
void Database::dbUndo()
{

}

//保存修改
void Database::dbSave()
{

}

//导出数据库表
void Database::exportTable()
{

}

//导入数据库表
void Database::importTable()
{

}
