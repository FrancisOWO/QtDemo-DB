# QtDemo-DB

Qt 连 MySQL 简单示例

### 目录结构

1）forms/: ui 文件

2）headers/: 头文件

3）sources/: 源文件

4）sql/: sql 文件

### 使用说明

1）在 MySQL 中导入 sql/ 目录下的 **import3.sql**，创建 demo 数据库并导入数据

注：import3.sql 为学生成绩数据库，来自数据库第 3 次实验，补充了创建新数据库的语句

2）在 sources/ 目录下的 **database.cpp** 中，修改 **Database::dbConnect()** 中连接数据库的**用户、密码**等设置

3）没了，运行一下试试看吧