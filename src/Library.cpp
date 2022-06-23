#include "Library.h"

Library::Library() {
}

string Library::buildId() {
	string BID = to_string(books.size() + 1);
	int n = BID.size();
	for (int i = 1; i <= 5 - n; i++) {
		BID = "0" + BID;
	}
	return BID;
}

//����Id����ͼ��Ľ���״̬
void Library::setFlag(string id, bool start) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getDel())
			continue;
		if (id == books[i].getId()) {
			books[i].setFlag(start);
			return;
		}
	}
}

void Library::setBooks(vector<Books> &books) {
	this->books = books;
}

//���,�����
bool Library::add(Base *b) {
	int n = books.size();
	//ǿ��ת������
	books.push_back((*(Books *)b));
	return n == books.size() - 1;
}

//ɾ��,�����
bool Library::remove(string id) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getDel() || !books[i].getFlag())
			continue;
		if (id.compare(this->books[i].getId()) == 0) {
//			books.erase(books.begin() + i );
			books[i].setDel(true);//�߼�ɾ��
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
		if (books[i].getDel() || !books[i].getFlag())
			continue;
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
		if (books[i].getDel())
			continue;
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
	printf("%-10s%-30s%-15s%10s\n", "���", "����", "����", "�Ƿ񱻽���");
	for (int i = 0; i < books.size(); i++) {
		//�������ע�߼�ɾ������ʾ
		if (books[i].getDel())
			continue;
		printf("%-10s%-30s%-15s",  books[i].getId().c_str(), books[i].getName().c_str(),
		       books[i].getItem().c_str() );
		if (books[i].getFlag()) {
			cout << "��" << endl;
		} else {
			cout << "��" << endl;
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