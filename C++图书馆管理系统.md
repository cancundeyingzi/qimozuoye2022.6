# C++图书馆管理系统

**开发语言：** C++

**开发工具：** Dev-cpp

**小组成员：**麦文鹏、陶翌晨、刘家乐、谷海斌、韩昱、曹魏薰

## 介绍

用C++编写的图书管理系统项目，包含图书信息和用户信息，具备对图书和读者的增删改查功能，以及借书还书功能。

## 项目特点及创新

### 1、登陆系统以及注册系统

<img src="C:\Users\Mai\Desktop\C++\C++期末大作业\基本\image\登陆界面.png" style="zoom:67%;float:left" />

登陆身份可分为**图书管理者**和**读者**

- 图书管理者
  1. 默认密码为`admin`
  2. 可以进行读者管理和图书管理
- 读者
  1. 可以通过注册获得账号，其账号将被**Readers**管理类所管理

密码将使用**MD5**加密算法保存在本地中，其过程是不可逆的

### 2、程序初始化以及一键保存(读取于写入)



### 3、采用不可逆的MD5加密算法对密码进行加密



### **4.采用管理类去管理基础对象，并提供对基础类的增删改查功能**

### 

### 5、图书书号(id)以及读者学号(id)，具备主键的唯一性和自增长性



### 6、引入新概念，逻辑删除







## 运行时截图

<img src="image\初始化界面.png" style="zoom:67%;float:left" />



<img src="C:\Users\Mai\Desktop\C++\C++期末大作业\基本\image\修改界面.png" style="zoom:67%;float:left" />



## 模块



### 全局变量

#### Library L;//图书管理类

#### Readers R;//读者管理类

#### vector<Record> records;//借书还书记录

#### string password = ""; //管理员密码

### 全局函数(部分)

#### **void Login();//登录模块**

#### **void writeDataToProperties();//写入模块**

#### **void readDataFromProperties();//读取模块**

#### **void init();//初始化**

#### **void administrators();//管理者**

#### **void bookManagment();//图书管理模块**

#### **void readerManagment();//读者管理模块**

#### **void record(reader &user);//借书还书模块**

#### string enCode(string key);//MD5加密



### 类

基础类**Base**和管理类**Managment**以及其子类

#### Base(基础类)

- ###### Books

- reader

- Record

#### Managment(管理类)

- Library
- Readers







### 