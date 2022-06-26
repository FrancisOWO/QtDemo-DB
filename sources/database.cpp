#include "database.h"
#include "ui_database.h"

#include <QDebug>

//字符串编码转换
QString CStr2LocalQStr(const char *str)
{
    return QString::fromUtf8(str);
}

Database::Database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database)
{
    ui->setupUi(this);

    InitMembers();
    InitConnections();
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
    connect(ui->pbtnUndo, SIGNAL(clicked()), this, SLOT(dbUndo()));     //撤销修改
    connect(ui->pbtnSave, SIGNAL(clicked()), this, SLOT(dbSubmit()));   //保存修改
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
        QMessageBox::critical(this, "连接失败", db.lastError().text());
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

    //隐藏不需要显示的列（比如自增主键）
    if("depts1" == tableName || "courses1" == tableName)
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
void Database::on_pbtnAdd_clicked()
{
    //在表格最下方新增一行
    int n = model->rowCount();
    model->insertRow(n);

    //隐藏了自增主键列的表，需要手动添加id
    if("depts1" == tableName || "courses1" == tableName){
        //若已存在记录，则取最后的id加1作为新id
        int pre_id = 1;
        if (n > 0) pre_id = model->data(model->index(n-1,0)).toInt();
        model->setData(model->index(n, 0), pre_id+1);   //设置id
    }
}

//删除记录
void Database::on_pbtnDel_clicked()
{
    //删除当前选中的行
    int cur = ui->tblShow->currentIndex().row();
    model->removeRow(cur);
}

//撤销修改
void Database::dbUndo()
{
    model->revertAll();     //撤销
    model->select();        //刷新model
}

//保存修改（手动提交）
void Database::dbSubmit()
{
    //弹窗询问：是否确定要将修改写入数据库
    QMessageBox box(QMessageBox::Question, CStr2LocalQStr("保存"),
                    CStr2LocalQStr("确定要保存修改到数据库？"),
                    QMessageBox::Yes | QMessageBox::No);
    //修改--快捷键Y，取消--快捷键N
    box.setButtonText(QMessageBox::Yes, CStr2LocalQStr("修改(&Y)"));
    box.setButtonText(QMessageBox::No, CStr2LocalQStr("取消(&N)"));
    int ret = box.exec();
    //选择"修改"
    if(QMessageBox::Yes == ret){
        int ok = model->submitAll();    //手动提交修改
        if(!ok) //提交失败
            QMessageBox::critical(this, CStr2LocalQStr("保存失败"), model->lastError().text());
        else    //提交成功
            QMessageBox::information(this, CStr2LocalQStr("提示"), CStr2LocalQStr("保存成功!"));

        model->select();        //刷新model
    }
}

//导出数据库表
void Database::exportTable()
{

}

//导入数据库表
void Database::importTable()
{

}
