#include "Library.h"

Library::Library() {
}

//根据Id设置图书的借阅状态
void Library::setFlag(string id, bool start) {
	for (int i = 0; i < books.size(); i++) {
		if (id == books[i].getId()) {
			books[i].setFlag(start);
			return;
		}
	}
}

void Library::setBooks(vector<Books> &books) {
	this->books = books;
}

//添加,已完成
bool Library::add(Base *b) {
	int n = books.size();
	//强制转换类型
	books.push_back((*(Books *)b));
	return n == books.size() - 1;
}

//删除,已完成
bool Library::remove(string id) {
	for (int i = 0; i < books.size(); i++) {
		if (id.compare(this->books[i].getId()) == 0) {
			books.erase(books.begin() + i );
			return true;
		}
	}
	return false;
}

//修改,默认已存在该id,已完成
bool Library::modify(Base *b) {
	Books *book = (Books *)b;
	string id = book->getId();
	for (int i = 0; i < books.size(); i++) {
		if (id == this->books[i].getId()) {
			books[i] = *book;
			return true;
		}
	}
	return false;
}

//按Id查询 已完成
Base *Library::selectById(string id) {
	Books *book = NULL;
	for (int i = 0; i < books.size(); i++) {
		if (id == this->books[i].getId()) {
			book = &books[i];
			break;
		}
	}
	//失败标志
	return book;
}

//查询所有 已完成
void Library::selectAll() {
	cout << "=========================================================================" << endl;
	if (books.size() == 0) {
		cout << "没有图书记录" << endl;
		return;
	}
	printf("%-10s%-30s%-15s%10s\n", "书号", "书名", "类型", "是否被借阅");
	for (int i = 0; i < books.size(); i++) {
		printf("%-10s%-30s%-15s",  books[i].getId().c_str(), books[i].getName().c_str(),
		       books[i].getItem().c_str() );
		if (books[i].getFlag()) {
			cout << "否" << endl;
		} else {
			cout << "是" << endl;
		}
	}
	cout << "=========================================================================" << endl;
}

int Library::getTotal() {
	return books.size();
}

vector<Books> &Library::getBooks() {
	return books;
}

Library::~Library() {
	delete &books;
}