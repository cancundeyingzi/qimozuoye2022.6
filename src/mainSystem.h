#include <iostream>
#include "Library.h"
#include "Readers.h"
#include "reader.h"
#include "Books.h"
#include "Record.h"

class mainSystem {
	private:
		Library L;//图书管理类
		Readers R;//读者管理类
		vector<Record> records;//借书还书记录
		string password; //管理员密码
	public:
		mainSystem();
		void init();
		int input();
		void run();
		void Login();//登录模块
		void writeDataToProperties();//写入模块
		void readDataFromProperties();//读取模块
		void administrators();//管理者
		void bookManagment();//图书管理模块
		void readerManagment();//读者管理模块
		void record(reader &user);//借书还书模块
		string enCode(string key);//MD5加密

};
