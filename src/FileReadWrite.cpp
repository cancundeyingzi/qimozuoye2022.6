#include "main.cpp"
extern Library L;//图书管理类
extern Readers R;//读者管理类

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
	try {
		if (!inf) {
			throw 1;
		}
		inf >> password;
	} catch (int) {
		cout << "文件:config\\key.dat不存在" << endl;
	}

	try {
		if (!inf_book) {
			throw 1;
		}
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
			//分别代表 id ,name ,type ,flag
			if (s[0] != "" && s[1] != "" && s[2] != "" && s[3] != "") {
				book.push_back(Books(s[0], s[1], s[2], s[3][0] == 'f' ? true : false));
			}
		}
	} catch (int) {
		cout << "文件:config\\library.dat不存在" << endl;
	}

	try {
		if (!inf_reader) {
			throw 1;
		}
		while (!inf_reader.eof()) {
			string str;
			inf_reader >> str;
			string s[3];
			for (int i = 0, j = 0; i < str.size(); i++) {
				if (str[i] == ',') {
					j++;
				} else {
					s[j] += str[i];
				}
			}
			//分别代表 id ,name ,tel
			if (s[0] != "" && s[1] != "" && s[2] != "") {
				readers.push_back(reader(s[0], s[1], s[2]));
			}
		}
	} catch (int) {
		cout << "文件:config\\readers.dat不存在" << endl;
	}



//	if (inf) {
//		inf >> password;
//	} else {
//		cout << "文件:config\\key.dat不存在" << endl;
//	}
//	if (!inf_book) {
//		cout << "文件:config\\library.dat不存在" << endl;;
//	}
//
//	if (!inf_reader) {
//		cout << "文件:config\\readers.dat不存在" << endl;
//	}
//	while (!inf_book && !inf_book.eof()) {
//		string str;
//		inf_book >> str;
//		string s[3];
//		for (int i = 0, j = 0; i < str.size(); i++) {
//			if (str[i] == ',') {
//				j++;
//			} else {
//				s[j] += str[i];
//			}
//		}
//		if (s[0] != "" && s[1] != "" && s[2] != "") {
//			book.push_back(Books(s[0], s[1], s[2]));
//		}
//	}
//	while (!inf_reader && !inf_reader.eof()) {
//		string str;
//		inf_reader >> str;
//		string s[3];
//		for (int i = 0, j = 0; i < str.size(); i++) {
//			if (str[i] == ',') {
//				j++;
//			} else {
//				s[j] += str[i];
//			}
//		}
//		if (s[0] != "" && s[1] != "" && s[2] != "") {
//			readers.push_back(reader(s[0], s[1], s[2]));
//		}
//	}

	R.setReaders(readers);
	L.setBooks(book);
	L.selectAll();
	inf.close();
	inf_book.close();
	inf_reader.close();
}

//一件保存数据
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