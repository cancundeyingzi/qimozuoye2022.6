# 图书馆管理系统

![](image\部分功能图.jpg)



## 登录功能(待完成)

功能：美化用户界面，通过用户输入的密码与全局变量password进行比较，对用户进行身份判断，通过则出现提示界面，提供诸如进入图书管理模块、读者管理模块、登记模块、保存数据、修改密码等功能。

## 图书馆里模块(待完成)

功能：美化用户界面，提供增删改查等功能。已声明全局变量L，其中封装了基础的增删改查方法，直接调用就行，所有与Books有关的数据都应该存储在L中。所提供的方法不对数据的有效性进行判别，自行编写代码对各种特殊情况进行判断，确保数据的正确性后再调用方法。

## 读者管理模块(待完成)

功能：美化用户界面，提供增删改查等功能。已声明全局变量R，其中封装了基础的增删改查方法，直接调用就行，所有与reader有关的数据都应该存储在R中。所提供的方法不对数据的有效性进行判别，自行编写代码对各种特殊情况进行判断，确保数据的正确性后再调用方法。

## 登记模块(待完成)

功能：美化用户界面，编写借书还书功能以及查询所有记录功能，已提供Record类，每条记录对应一个Record对象，最后将其存储至vector<Record> record容器中;

## 数据初始化与存储（完成)

从文件中读取数据进行初始化，退出程序时可以选择保存数据。

可读取的数据有管理员密码password,图书数据，读者数据，登记数据。

```c++
void readDataFromProperties() {
	cout << "开始读取" << endl;
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	vector<Books> book;
	vector<reader> readers;
	if (inf) {
		inf >> password;
		password = deCode(password);
	} else {
		cout << "文件:config\\key.dat不存在" << endl;
	}
	if (!inf_book) {
		cout << "文件:config\\library.dat不存在" << endl;;
	}

	if (!inf_reader) {
		cout << "文件:config\\readers.dat不存在" << endl;
	}
	while (!inf_book.eof()) {
		string str;
		inf_book >> str;
		string s[3];
		for (int i = 0, j = 0; i < str.size(); i++) {
			if (str[i] == ',') {
				j++;
			} else {
				s[j] += str[i];
			}
		}
		if (s[0] != "" && s[1] != "" && s[2] != "") {
			book.push_back(Books(s[0], s[1], s[2]));
		}
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
		if (s[0] != "" && s[1] != "" && s[2] != "") {
			readers.push_back(reader(s[0], s[1], s[2]));
		}
	}
	R.setReaders(readers);
	L.setBooks(book);
	inf_book.close();
	inf_reader.close();
}
//写入数据
void writeDataToProperties() {
	vector<Books> book = L.getBooks();
	vector<reader> readers = R.getReaders();
	ofstream outf_book("config\\library.dat", ios:: out);
	ofstream outf_reader("config\\readers.dat", ios:: out );
	ofstream outf_key("config\\key.dat", ios::out);
	//用于保存内容
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
		outf_key << enCode(password.c_str());
	}
	outf_reader.close();
	outf_book.close();
	outf_key.close();
}
```



## 文本加密解密(已完成)

提供文本的加密解密功能

```c++
string enCode(string key) {
	string result;
	for (int i = 0; i < key.size(); i++) {
		if (key[i] >= 'A' && key[i] <= 'Z') {
			result += char((key[i] + 15 - 65) % 26 + 65);
		} else if (key[i] >= 'a' && key[i] <= 'z') {
			result += char((key[i] + 15 - 97) % 26 + 97);
		} else if (key[i] >= '0' && key[i] <= '9') {
			result += char((key[i] + 15 - 48) % 26 + 48);
		} else {
			result = "非法密码";
		}
	}
	return result;
}

string deCode(string key) {
	string result;
	for (int i = 0; i < key.size(); i++) {
		if (key[i] >= 'A' && key[i] <= 'Z') {
			result += char((((key[i] - 65) + 26) - 15) % 26 + 65);
		} else if (key[i] >= 'a' && key[i] <= 'z') {
			result += char((((key[i] - 97) + 26) - 15) % 26 + 97);
		} else if (key[i] >= '0' && key[i] <= '9') {
			result += char((((key[i] - 48) + 26) - 15) % 26 + 48);
		} else {
			result = "非法密码" ;
		}
	}
	return result;
}
```





# API

为了简化开发和统一格式，我已在开发初期将一系列基础功能封装好，后期实现具体功能调用方法即可。

请自行编写代码对数据的有效性进行判断,**过滤非法数据**后后再调用方法。

![](image\继承体系.png)

## LibraryImpl类

**图书馆管理类**

### **成员变量**:

一个可以无限扩容的容器，用于存储Books对象,使用方法与数组一致

```C++
vector<Books> books;
```

### **方法**：

​	**设置某本书的借阅状态**,False代表已被借走

​	void setFlag(string id,bool start);

​	**添加数据，传入Books对象**,返回值是否成功添加

​	bool add(Base *b);

​	**删除数据,传入id**,返回值是否成功删除

​	bool remove(string id);

​	**修改数据，传入已修改的Books对象**,确保id一致，自动根据该对象的Id替换原有数据

​	bool modify(Base *b);

​	**按Id查询，成功则返回该对象的toString()方法**,失败则返回""，判断是否有该条数据，判断其返回结果长度是否为>1即可

​	string selectById(string id);

​	**查询所有**

​	void selectAll();

​	**获取Books容器**

​	vector<Books>& getBooks();

![](C:\Users\Mai\Desktop\图书管理系统\image\LibraryImpl.png)

## Readers类

**读者管理类**

功能与LibraryImpl类似，自行查阅源码

![](C:\Users\Mai\Desktop\图书管理系统\image\Readers.png)

## Record类

**记录类**，提供简单的get方法和toString方法,每次创建该对象，都会自动给其date属性设置当前时间

![](C:\Users\Mai\Desktop\图书管理系统\image\Record.png)

## Books类

书籍，基础类

string toString() 将id、name、type、start拼接成字符串后返回

提供setStart()方法设置其状态，其中start为**false**时表示书已借出

## reader类

读者，基础类

string toString() 将id name tel拼接成字符串后返回







## Vector容器的基本使用

![](image\Vector容器的基本使用.png)

