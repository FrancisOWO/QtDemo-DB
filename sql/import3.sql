
-- 创建数据库
create database demo;
-- 切换数据库
use demo;

-- 显示当前数据库
select database();

-- 学院
create table depts1 (
	no integer primary key not null,
	name varchar(30) not null
);

-- 学生
create table students1 (
	no integer primary key not null,
	name varchar(20) not null,
	gender varchar(6) not null check (gender in ('Male','Female')),
	age integer not null,
	d_no integer not null, 
	constraint st_c_1 foreign key (d_no) references depts1(no)
);

-- 课程
create table courses1 (
	no integer primary key not null,
	name varchar(20) not null,
	credit integer not null,
	d_no integer not null,
	constraint co_c_1 foreign key (d_no) references depts1(no)
);

-- 分数
create table scores1 (
	s_no integer not null,
	c_no integer not null,
	score integer not null,
	constraint sc_c_1 foreign key (s_no) references students1(no),
	constraint sc_c_2 foreign key (c_no) references courses1(no)
);

-- 学院
insert into depts1 (no,name) values (1,'Computer Science');
insert into depts1 (no,name) values (2,'Mathematics');
insert into depts1 (no,name) values (3,'Architecture');
insert into depts1 (no,name) values (4,'Management');

-- 课程
insert into courses1 (no,name,credit,d_no) values (1,'Database',5,1);
insert into courses1 (no,name,credit,d_no) values (2,'Mathematics',2,2);
insert into courses1 (no,name,credit,d_no) values (3,'Information System',1,4);
insert into courses1 (no,name,credit,d_no) values (4,'Operating System',6,1);
insert into courses1 (no,name,credit,d_no) values (5,'Data Structure',4,1);
insert into courses1 (no,name,credit,d_no) values (6,'Data Processing',2,4);
insert into courses1 (no,name,credit,d_no) values (7,'PASCAL',3,1);

-- 学生
insert into students1 (no,name,gender,age,d_no) values (200215120,'Mike','Male',21,3);
insert into students1 (no,name,gender,age,d_no) values (200215121,'Tom','Male',20,1);
insert into students1 (no,name,gender,age,d_no) values (200215122,'Jerry','Female',19,1);
insert into students1 (no,name,gender,age,d_no) values (200215123,'Alice','Female',18,2);
insert into students1 (no,name,gender,age,d_no) values (200215125,'Bob','Male',19,3);

-- 分数
insert into scores1 (s_no,c_no,score) values (200215121,1,92);
insert into scores1 (s_no,c_no,score) values (200215121,2,85);
insert into scores1 (s_no,c_no,score) values (200215121,3,88);
insert into scores1 (s_no,c_no,score) values (200215122,2,90);
insert into scores1 (s_no,c_no,score) values (200215122,3,80);

select * from students1;
select * from courses1;
select * from depts1;
select * from scores1;
