#include "mainSystem.h"

mainSystem::mainSystem() {
	this->password = "";
}

void mainSystem::init() {
	readDataFromProperties();
//	system("pause");
}

void mainSystem::run() {
	Login();
}

//输入校验
int mainSystem::input() {
	int select;
	cin >> select;
	while (cin.fail()) { //如果输入类型和定义类型不一致为true
		if (cin.fail()) {
			cout << "输入选项不合法！！！" << endl;
			cin.clear();
			cout << "请重新输入" << endl;
			while (cin.get() != '\n') {
				continue;
			}
			cin >> select;
		}
	}
	return select;
}

//登录模块
void mainSystem::Login() {
	system("cls");
	while (1) {
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||" << "\t\t    图书馆管理系统" << "\t\t  ||" << endl;
		cout << "||------------------------------------------------||" << endl;
		cout << "||    1-管理员    2-用户    3-注册用户    0-退出  ||" << endl;
		cout << "||================================================||" << endl;
		cout << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
		int select;
		cout << "请选择你的操作：";
		select = input();
		switch (select) {
			case 0:
				cout << "退出成功";
				return;
			case 1: {
				//如果密码为空则使用默认密码
				if (password == "") {
					password = enCode("admin");
				}
				string pwd;
				cout << "请输入管理员密码:" ;
				cin >> pwd;
				if (enCode(pwd) == password) {
					cout << "登陆成功" << endl;
					system("cls");
					administrators();
				} else {
					system("cls");
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
				if (user != NULL) {
					if (user->check(enCode(pwd))) {
						system("cls");
						record(*user);
					} else {
						system("cls");
						cout << "登陆失败" << endl;
					}
				} else {
					system("cls");
					cout << "学号不存在,请重新输入" << endl;
				}
			}
			break;
			//注册
			case 3: {
				string name, tel, pwd;
				cout << "姓名：";
				cin >> name;
				cout << "密码：";
				cin >> pwd;
				cout << "手机号码：";
				cin >> tel;
				//生成id
				string id = R.buildId();
				reader r(id, name, tel, enCode(pwd));
				R.add(&r);
				system("cls");
				cout << "[提示]注册成功，请牢记你的学号：" << r.getId() << endl;
				break;
			}
			default:
				system("cls");
				cout << "错误功能不存在请返回！" << endl;
				break;
		}

	}

}

//写入模块
void mainSystem::writeDataToProperties() {
	cout << "[提示]自动保存..." << endl;
	//获取内存中的数据
	vector<Books> book = L.getBooks();
	vector<reader> readers = R.getReaders();
	//创建流对象
	ofstream outf_book("config\\library.dat", ios:: out);
	ofstream outf_reader("config\\readers.dat", ios:: out );
	ofstream outf_key("config\\key.dat", ios::out);
	ofstream outf_record("config\\records.dat", ios::out);
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

	val = "";
	for (int i = 0; i < records.size(); i++) {
		val += records[i].Out();
	}
	outf_record << val;

	//保存密码
	if (password != "") {
		//加密
		outf_key << password.c_str();
	}

	outf_record.close();
	outf_reader.close();
	outf_book.close();
	outf_key.close();
}

//读取模块
void mainSystem::readDataFromProperties() {
//	cout << "[提示]程序初始化......" << endl;
	//创建流对象
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	ifstream inf_record("config\\records.dat", ios::in);
	//创建容器
//	cout << "[提示]容器已创建......" << endl;
	vector<Books> book;
	vector<reader> readers;
	int bookNum = 0, readerNum = 0, recordNum = 0;
	//文件异常处理

	if (inf) {
		inf >> password;

	} else {
		cout << "[警告]文件:config\\key.dat不存在" << endl;
	}

	if (!inf_book) {
		cout << "[警告]文件:config\\library.dat不存在" << endl;

	} else {
		while (!inf_book.eof()) {
			string str;
			inf_book >> str;
			string s[6];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			if (s[0] != "" && s[1] != "" && s[2] != "") {
				book.push_back(Books(s[0], s[1], s[2], s[3][0] == 'f' ? false : true, s[4][0] == 't' ? true : false, s[5]));
				bookNum++;
			}
		}
		L.setBooks(book);
	}

	if (!inf_reader) {
		cout << "[警告]文件:config\\readers.dat不存在" << endl;

	} else {
		while (!inf_reader.eof()) {
			string str;
			inf_reader >> str;
			string s[5];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			if (s[0] != "" && s[1] != "" && s[2] != "" ) {
				readers.push_back(reader(s[0], s[1], s[2], s[3], s[4][0] == 't' ? true : false));
				readerNum++;
			}
		}
		R.setReaders(readers);
	}

	if (!inf_record) {
		cout << "[警告]文件:config\\records.dat不存在" << endl;;

	} else {
		string str;
		while (getline(inf_record, str)) {
			string s[6];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			if (s[0] != "" && s[1] != "" && s[2] != "" ) {
				records.push_back(Record(s[0], s[1], s[2], s[3],  s[5] == "借书" ? false : true, s[4]));
				recordNum++;
			}
		}
	}
//	cout << "[提示]共读取书籍记录" << bookNum << "条" << ",";
//	cout << "读者记录" << readerNum << "条" << endl;
//	L.selectAll();
//	R.selectAll();
//	cout << "[提示]程序初始化完成！\n";
	inf.close();
	inf_book.close();
	inf_reader.close();
}

//管理者
void mainSystem::administrators() {
	while (1) {
		system("cls");
		cout << "__________________________________________________________________________" << endl;
		cout << "||======================================================================||" << endl;
		cout << "||" << "                           欢迎进入管理员系统                         ||" << endl;
		cout << "||======================================================================||" << endl;
		cout << "||" << "    1-图书管理  2-读者管理  3-修改密码  4-查询借阅记录  0-退出        ||" << endl;
		cout << "||======================================================================||" << endl;
		cout << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
		int select = input();
		switch (select) {
			case 0:
				system("cls");
				cout << "退出成功";
				return;
			case 1:
				bookManagment();
				break;
			case 2:
				readerManagment();
				break;
			case 3: {
				cout << "请输入原密码:";
				string pwd, newPwd;
				cin >> pwd;
				if (enCode(pwd)  == password) {
					cout << "请输入新密码";
					cin >> newPwd;
					password = enCode(newPwd);
					writeDataToProperties();
				} else {
					cout << "密码错误，请尝试！" << endl;
				}
				break;
			}
			case 4:
				cout << "________________________________________________________________________________" << endl;
				cout << "||=============================================================================||" << endl;
				for (int i = 0; i < records.size(); i++) {
					cout << "||" ;
					records[i].toString();
				}
				cout << "||=============================================================================||" << endl;
				cout << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
				system("pause");
				break;
			default:
				system("cls");
				cout << "错误功能不存在请返回！" << endl;
				break;
		}
	}
}

void mainSystem::bookManagment() {
	while (1) {
		system("cls");
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||\t\t    " << "1-查询所有图书" << "\t\t  ||" << endl;
		cout << "||\t\t    " << "2-新增图书" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "3-删除图书" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "4-修改图书" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "5-查询图书" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "6-退出" << "\t\t\t  ||" << endl;
		cout << "||================================================||" << endl;
		cout << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
		string name, item, id, flag;
		int select = input();
		system("cls");
		switch (select) {
			//查询所有
			case 1:
				L.selectAll();
				break;
			case 2:
				//添加功能
			{
				//管理类分配ID
				id = L.buildId();
				cout << "请输入书名:";
				cin >> name;
				cout << "请输入类型:";
				cin >> item;
				Books b(id, name, item, true);
				L.add(&b);
				writeDataToProperties();
			}
			break;

			case 3: {
				L.selectAll();
				cout << "请输入书号" << endl;
				cin >> id;
				if (!((Books *)L.selectById(id))->getFlag()) {
					//被借走的情况应该说明
					cout << "这本书被借走了" << endl;
					break;
				}
				if (L.remove(id)) {
					cout << "删除成功" << endl;
					writeDataToProperties();
				} else {
					cout << "不存在这本书,请重新查询" << endl;
				}
			}
			break;
			case 4:
				//修改功能
			{
				L.selectAll();
				cout << "请输入书号：" ;
				cin >> id;
				Books *book = (Books *)L.selectById(id);
				if (book == NULL) {
					cout << "不存在这本书,请重新查询" << endl;
				} else if (!book->getFlag()) {
					//被借走的情况应该说明
					cout << "这本书被借走了" << endl;
				} else {
					cout << "书名：";
					cin >> name;
					cout << "类别：";
					cin >> item;
					cout << "借阅状态(Y/N):";
					cin >> flag;
					Books b(id, name, item, flag == "Y" ? true : false);
					L.modify(&b);
					writeDataToProperties();
				}
			}
			break;
			case 5: {
				L.selectAll();
				cout << "请输入书号" << endl;
				cin >> id;
				Books *book = (Books *)L.selectById(id);
				if (book == NULL) {
					cout << "不存在这本书,请重新查询" << endl;
				} else {
					cout << book->toString();
				}
			}
			break;
			case 6:
				return;
				break;
			default:
				system("cls");
				cout << "错误功能不存在请返回！" << endl;
				break;
		}
		cout << "按任意键继续";
		getchar();
		getchar();
	}
}

void mainSystem::readerManagment() {
	while (1) {
		system("cls");
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||\t\t    " << "1-查询所有读者" << "\t\t  ||" << endl;
		cout << "||\t\t    " << "2-新增读者" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "3-删除读者" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "4-修改读者" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "5-查询读者" << "\t\t\t  ||" << endl;
		cout << "||\t\t    " << "6-退出    " << "\t\t\t  ||" << endl;
		cout << "||================================================||" << endl;
		cout << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣" << endl;
		string name, tel, id;
		int select = input();
		system("cls");
		switch (select) {
			//查询所有
			case 1:
				R.selectAll();
				break;
			case 2:
				//添加功能
			{
				id = R.buildId();
				cout << "请输入姓名:";
				cin >> name;
				cout << "请输入手机号码:";
				cin >> tel;
				reader r(id, name, tel, "");
				R.add(&r);
				writeDataToProperties();
			}
			break;

			case 3: {
				R.selectAll();
				cout << "请输入学号" << endl;
				cin >> id;
				if (R.remove(id)) {
					cout << "删除成功" << endl;
				} else {
					cout << "不存在此人,请重新查询" << endl;
					writeDataToProperties();
				}
			}
			break;
			case 4:
				//修改功能
			{
				R.selectAll();
				cout << "请输入学号：" ;
				cin >> id;
				reader *r = (reader *)R.selectById(id);
				if (r == NULL) {
					cout << "不存在此人,请重新查询" << endl;
				} else {
					cout << "姓名：";
					cin >> name;
					cout << "手机号：";
					cin >> tel;
					reader reader(id, name, tel, r->getPassword());
					R.modify(&reader);
					writeDataToProperties();
				}
			}
			break;
			case 5: {
				R.selectAll();
				cout << "请输入学号" << endl;
				cin >> id;
				reader *r = (reader *)R.selectById(id);
				if (r == NULL) {
					cout << "不存在此人,请重新查询" << endl;
				} else {
					cout << r->toString();
				}
			}
			break;
			case 6:
				return;
				break;
			default:
				system("cls");
				cout << "错误功能不存在请返回！" << endl;
				break;
		}
		system("pause");
	}
}

void mainSystem::record(reader &user) {
	int arr;
	Record J;
	Books *book;
	string id;
	string j_pwd;
	string x_pwd;
	while (1) {
		vector<Books> books = L.getBooks();
		cout << "||===================================================================||" << endl;
		printf("%-10s%-30s%-15s%10s\n", "||书号", "    书名", "  类型", "    是否被借阅||");
		for (int i = 0; i < books.size(); i++) {
			if (books[i].getReaderId() == user.getId()) {
				arr++;
				printf("||%-10s%-30s%-15s%8s\n", books[i].getId().c_str(), books[i].getName().c_str(), books[i].getItem().c_str(),
				       "      是    ||");
			}
		}
		cout << "||===================================================================||" << endl;
		cout << "||请选择您的操作   1.借书   2.还书   3.修改密码   4.退出登入         ||" << endl;
		cout << "||===================================================================||" << endl;
		string t;
		cout << "请选择你的操作:";
		cin >> t;
		if (t == "1") {
			system("cls");
			cout << "(返回请按9)当前图书馆图书如下：" << endl;
			L.selectAll();

			do {
				cout << "(返回请按9)请输入你想借的书的ID:";
				cin >> id;
				book = (Books *)L.selectById(id);
				if ( id == "9") {
					system("cls");
					break;
				} else if (book == NULL) {
					cout << "不存在这本书,请重新查询" << endl;
				} else if (book->getFlag() == false ) {
					cout << "这本书已被借走" << endl;
				} else {
					arr++;
					book->setReaderId(user.getId());
					book->setFlag(false);
					L.modify(book);
					system("cls");
					cout << "借书成功" << endl;
					Record J(book->getReaderId(), book->getName(), user.getId(), user.getName(), false); //借书
					J.toString();
					records.push_back(J);
					writeDataToProperties();
					break;
				}
			} while (1);
		} else if (t == "2") {
			if (arr == 0) {
				cout << "该用户未借过书请重新输入" << endl ;
			} else {
				do {
					cout << "(返回请按9)请输入您要归还书的ID:" ;
					cin >> id;
					book = (Books *)L.selectById(id);
					if (id == "9") {
						system("cls");
						break;
					} else if (book == NULL) {
						cout << "输入错误" << endl;
					} else if (book->getReaderId() == user.getId()) {
						book->setReaderId("null");
						book->setFlag(true);
						L.modify(book);
						system("cls");
						cout << "还书成功" << endl;
						Record J(book->getReaderId(), book->getName(), user.getId(), user.getName(), true);
						J.toString();
						records.push_back(J);
						writeDataToProperties();
						break;
					} else {
						cout << "您并未借阅此书" << endl;;
					}
				} while (1);
			}
		} else if (t == "3") {
			cout << "请输入你的旧密码:";
			cin >> j_pwd;
			if (user.getPassword() == enCode(j_pwd)) {
				cout << "请输入你的新密码:";
				cin  >> x_pwd;
				user.setPwd(enCode(x_pwd));
				R.modify(&user);
				writeDataToProperties();
				system("cls");
				cout << "修改成功";
			} else {
				system("cls");
				cout << "旧密码错误返回" << endl;
			}
		} else if (t == "4") {
			cout << "退出成功" << endl;
			break;
		} else {
			system("cls");
			cout << "暂无此操作，请按提示操作" << endl;
		}
	}
	system("cls");
}

string mainSystem::enCode(string key) {
	string result;
	string md(string key);
	result = md(key);
	return result;
}