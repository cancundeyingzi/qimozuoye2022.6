#include <iostream>
#include "Library.h"
#include "Readers.h"
#include "reader.h"
#include "Books.h"
#include "Record.h"
using namespace std;
void Login();
void writeDataToProperties();
void readDataFromProperties();
void init();
void bookManagment();
void readerManagment();
string enCode(string key);
Library L;//图书管理类
Readers R;
vector<Record> records;//借书还书记录
void record(reader &user);
string password = ""; //管理员密码
void administrators();

int main() {
	string key="hello";
	cout<<enCode(key);
}

//初始化，调试模拟数据
void init() {
	readDataFromProperties();
	bookManagment();
}

void registerUser() {
	string name, tel, pwd;
	cout << "姓名：";
	cin >> name;
	cout << "密码：";
	cin >> pwd;
	cout << "手机号码：";
	cin >> tel;
	//生成id
	string id = to_string(R.getTotal() + 1);
	int n = id.size();
	for (int i = 0; i < 5 - n; i++) {
		id = "0" + id;
	}
	reader r(id, name, tel, pwd);
	R.add(&r);
	cout << "注册成功，请牢记你的学号：" << r.getId() << endl;
}

/**
登录模块：
	需完成功能:
		1、制作简单的登录界面，只有一个管理员用户，可以对三大模块进行操作
			每次操作调用cls清除屏幕;
		2、判断账号密码有效性,登录一次即可
		3、死循环保证返回到本模块后可以继续操作
**/
void Login() {
	while (1) {
		cout << "===============================" << endl;
		cout << "||" << "\t\t图书馆管理系统" << endl;
		cout << "===============================" << endl;
		cout << "请选择你的身份 1-管理员 2-用户 3-注册用户 0-退出" << endl;
		int select;
		cin >> select;
		switch (select) {
			case 0:
				return;
			case 1: {
				//如果密码为空则使用默认密码
				if (password.empty()) {
					password = enCode("admin");
				}
				string pwd;
				cout << "请输入管理员密码" << endl;
				cin >> pwd;
				if (enCode(pwd) == password) {
					cout << "登陆成功" << endl;
					administrators();
				} else {
					cout << "密码错误" << endl;
				}
				break;
			}
			case 2: {
				//根据id获取对象，使用check方法判断密码合法性
				string id, pwd;
				cout << "请输入学号:";
				cin >> id;
				cout << "请输入密码:";
				cin >> pwd;
				reader *user = (reader *)R.selectById(id);
				if (user->check(pwd)) {
					record(*user);
				} else {
					cout << "登陆失败" << endl;
				}
			}
			break;
			//注册
			case 3:
				registerUser();
				break;
		}

	}

}

void administrators() {
	cout << "===============================" << endl;
	cout << "欢迎进入管理员系统" << endl;
	cout << "1-图书管理\t2-读者管理\t0-退出" << endl;
	cout << "===============================" << endl;
	while (1) {
		int select;
		cin>>select;
		switch (select) {
			case 0:
				return;
			case 1:
				bookManagment();
				break;
			case 2:
				readerManagment();
				break;
		}
	}
}

//初始化读取数据
void readDataFromProperties() {
	cout << "开始读取" << endl;
	//创建流对象
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	//创建容器
	vector<Books> book;
	vector<reader> readers;
	//文件异常处理

	if (inf) {
		inf >> password;
	} else {
		cout << "文件:config\\key.dat不存在" << endl;
	}
	if (!inf_book) {
		cout << "文件:config\\library.dat不存在" << endl;;
	} else {
		while (!inf_book.eof()) {
			string str;
			inf_book >> str;
			string s[4];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			if (s[0] != "" && s[1] != "" && s[2] != "") {
				book.push_back(Books(s[0], s[1], s[2], s[3][0] == 'f' ? false : true));
			}
		}
		L.setBooks(book);
	}
	if (!inf_reader) {
		cout << "文件:config\\readers.dat不存在" << endl;
	} else {
		while (!inf_reader.eof()) {
			string str;
			inf_reader >> str;
			string s[4];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			if (s[0] != "" && s[1] != "" && s[2] != "" ) {
				readers.push_back(reader(s[0], s[1], s[2], s[3]));
			}
		}
		R.setReaders(readers);
	}

	L.selectAll();
	inf.close();
	inf_book.close();
	inf_reader.close();
}

//一键保存数据
void writeDataToProperties() {
	cout << "开始写入" << endl;
	//获取内存中的数据
	vector<Books> book = L.getBooks();
	vector<reader> readers = R.getReaders();
	//创建流对象
	ofstream outf_book("config\\library.dat", ios:: out);
	ofstream outf_reader("config\\readers.dat", ios:: out );
	ofstream outf_key("config\\key.dat", ios::out);
	//将数据保存到string一并写入
	string val = "";
	for (int i = 0; i < book.size(); i++) {
		val += book[i].toString().c_str();
	}
	outf_book << val;
	val = "";
	for (int i = 0; i < readers.size(); i++) {
		val += readers[i].toString().c_str();
	}
	outf_reader << val;
	//保存密码
	if (password != "") {
		//加密
		outf_key << enCode(password.c_str());
	}
	outf_reader.close();
	outf_book.close();
	outf_key.close();
}

string enCode(string key) {
	string result;
	string md(string key);
	result=md(key);
	//cout<<result<<endl;
	return result;
}




/**
图书管理模块：
	需完成功能:
		1、制作简单的用户界面，每次操作调用cls清除屏幕;
		2、基础的增删改查(调用方法已封装在LibraryImpl类中);
		3、处理各种特殊情况，比如进行添加用户前，先判断新增用户的数据是否合法
**/
void BookMsg() {
	cout << "===============================" << endl;
	cout << "1-查询所有图书" << endl;
	cout << "2-新增图书" << endl;
	cout << "3-删除图书" << endl;
	cout << "4-修改图书" << endl;
	cout << "5-查询图书" << endl;
	cout << "6-一键保存" << endl;
	cout << "===============================" << endl;
}

void bookManagment() {
	while(1){
		BookMsg();
		string name, item, id, flag;
		int select;
		cin >> select;
		switch (select) {
			//查询所有
			case 1:
				L.selectAll();
				break;
			case 2:
				//添加功能
			{
				id = to_string(L.getTotal()+1);
				int n=id.size();
				for (int i = 0; i <= 4 - n; i++ ) {
					id = "0" + id;
				}
				cout << "请输入书名:";
				cin >> name;
				cout << "请输入类型:";
				cin >> item;
				Books b(id, name, item, true);
				L.add(&b);
			}
			break;
	
			case 3: {
				cout << "请输入书号" << endl;
				cin >> id;
				if (L.remove(id)) {
					cout << "删除成功" << endl;
				} else {
					cout << "不存在这本书,请重新查询" << endl;
				}
			}
			break;
			case 4:
				//修改功能
			{
				cout << "请输入书号：" ;
				cin >> id;
				Books* book = (Books*)L.selectById(id);
				if (book == NULL) {
					cout << "不存在这本书,请重新查询" << endl;
				} else {
					cout << "书名：";
					cin >> name;
					cout << "类别：";
					cin >> item;
					cout << "借阅状态(Y/N):";
					cin >> flag;
					Books b(id, name, item, flag == "Y" ? true : false);
					L.modify(&b);
				}
			}
			break;
			case 5: {
				cout << "请输入书号" << endl;
				cin >> id;
				Books* book = (Books*)L.selectById(id);
				if (book ==NULL) {
					cout << "不存在这本书,请重新查询" << endl;
				} else {
					cout << book->toString();
				}
			}
			break;
			case 6:
				writeDataToProperties();
				break;
		}
	}
}


/**
读者管理模块：
	需完成功能:
		1、制作简单的用户界面，每次操作调用cls清除屏幕;
		2、基础的增删改查(调用方法已封装在Readers类中);
		3、处理各种特殊情况，比如进行添加用户前，先判断新增用户的数据是否合法
**/
void readerManagment() {

}

//借阅登记模块
void record(reader &user) {
	cout << user.toString();
}

