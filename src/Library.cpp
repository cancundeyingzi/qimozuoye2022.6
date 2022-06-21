#include "Library.h"

Library::Library() {
}

//����Id����ͼ��Ľ���״̬
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

//����,�����
bool Library::add(Base *b) {
	int n = books.size();
	//ǿ��ת������
	books.push_back((*(Books *)b));
	return n == books.size() - 1;
}

//ɾ��,�����
bool Library::remove(string id) {
	for (int i = 0; i < books.size(); i++) {
		if (id.compare(this->books[i].getId()) == 0) {
			books.erase(books.begin() + i );
			return true;
		}
	}
	return false;
}

//�޸�,Ĭ���Ѵ��ڸ�id,�����
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

//��Id��ѯ �����
Base *Library::selectById(string id) {
	Books *book = NULL;
	for (int i = 0; i < books.size(); i++) {
		if (id == this->books[i].getId()) {
			book = &books[i];
			break;
		}
	}
	//ʧ�ܱ�־
	return book;
}

//��ѯ���� �����
void Library::selectAll() {
	cout << "=========================================================================" << endl;
	if (books.size() == 0) {
		cout << "û��ͼ���¼" << endl;
		return;
	}
	printf("%-10s%-10s%-15s%-15s%10s\n", "�к�", "���", "����", "����", "�Ƿ񱻽���");
	for (int i = 0; i < books.size(); i++) {
		printf("%-10d%-10s%-15s%-15s", i, books[i].getId().c_str(), books[i].getName().c_str(),
		       books[i].getItem().c_str() );
		if (books[i].getFlag()) {
			cout << "��" << endl;
		} else {
			cout << "��" << endl;
		}
	}
	cout << "=========================================================================" << endl;
}

vector<Books> &Library::getBooks() {
	return books;
}

Library::~Library() {
	delete &books;
}