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
Library L;//ͼ�������
Readers R;
vector<Record> records;//���黹���¼
void record(reader &user);
string password = ""; //����Ա����
void administrators();

int main() {
	string key="hello";
	cout<<enCode(key);
}

//��ʼ��������ģ������
void init() {
	readDataFromProperties();
	bookManagment();
}

void registerUser() {
	string name, tel, pwd;
	cout << "������";
	cin >> name;
	cout << "���룺";
	cin >> pwd;
	cout << "�ֻ����룺";
	cin >> tel;
	//����id
	string id = to_string(R.getTotal() + 1);
	int n = id.size();
	for (int i = 0; i < 5 - n; i++) {
		id = "0" + id;
	}
	reader r(id, name, tel, pwd);
	R.add(&r);
	cout << "ע��ɹ������μ����ѧ�ţ�" << r.getId() << endl;
}

/**
��¼ģ�飺
	����ɹ���:
		1�������򵥵ĵ�¼���棬ֻ��һ������Ա�û������Զ�����ģ����в���
			ÿ�β�������cls�����Ļ;
		2���ж��˺�������Ч��,��¼һ�μ���
		3����ѭ����֤���ص���ģ�����Լ�������
**/
void Login() {
	while (1) {
		cout << "===============================" << endl;
		cout << "||" << "\t\tͼ��ݹ���ϵͳ" << endl;
		cout << "===============================" << endl;
		cout << "��ѡ�������� 1-����Ա 2-�û� 3-ע���û� 0-�˳�" << endl;
		int select;
		cin >> select;
		switch (select) {
			case 0:
				return;
			case 1: {
				//�������Ϊ����ʹ��Ĭ������
				if (password.empty()) {
					password = enCode("admin");
				}
				string pwd;
				cout << "���������Ա����" << endl;
				cin >> pwd;
				if (enCode(pwd) == password) {
					cout << "��½�ɹ�" << endl;
					administrators();
				} else {
					cout << "�������" << endl;
				}
				break;
			}
			case 2: {
				//����id��ȡ����ʹ��check�����ж�����Ϸ���
				string id, pwd;
				cout << "������ѧ��:";
				cin >> id;
				cout << "����������:";
				cin >> pwd;
				reader *user = (reader *)R.selectById(id);
				if (user->check(pwd)) {
					record(*user);
				} else {
					cout << "��½ʧ��" << endl;
				}
			}
			break;
			//ע��
			case 3:
				registerUser();
				break;
		}

	}

}

void administrators() {
	cout << "===============================" << endl;
	cout << "��ӭ�������Աϵͳ" << endl;
	cout << "1-ͼ�����\t2-���߹���\t0-�˳�" << endl;
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

//��ʼ����ȡ����
void readDataFromProperties() {
	cout << "��ʼ��ȡ" << endl;
	//����������
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	//��������
	vector<Books> book;
	vector<reader> readers;
	//�ļ��쳣����

	if (inf) {
		inf >> password;
	} else {
		cout << "�ļ�:config\\key.dat������" << endl;
	}
	if (!inf_book) {
		cout << "�ļ�:config\\library.dat������" << endl;;
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
		cout << "�ļ�:config\\readers.dat������" << endl;
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

//һ����������
void writeDataToProperties() {
	cout << "��ʼд��" << endl;
	//��ȡ�ڴ��е�����
	vector<Books> book = L.getBooks();
	vector<reader> readers = R.getReaders();
	//����������
	ofstream outf_book("config\\library.dat", ios:: out);
	ofstream outf_reader("config\\readers.dat", ios:: out );
	ofstream outf_key("config\\key.dat", ios::out);
	//�����ݱ��浽stringһ��д��
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
	//��������
	if (password != "") {
		//����
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
ͼ�����ģ�飺
	����ɹ���:
		1�������򵥵��û����棬ÿ�β�������cls�����Ļ;
		2����������ɾ�Ĳ�(���÷����ѷ�װ��LibraryImpl����);
		3�����������������������������û�ǰ�����ж������û��������Ƿ�Ϸ�
**/
void BookMsg() {
	cout << "===============================" << endl;
	cout << "1-��ѯ����ͼ��" << endl;
	cout << "2-����ͼ��" << endl;
	cout << "3-ɾ��ͼ��" << endl;
	cout << "4-�޸�ͼ��" << endl;
	cout << "5-��ѯͼ��" << endl;
	cout << "6-һ������" << endl;
	cout << "===============================" << endl;
}

void bookManagment() {
	while(1){
		BookMsg();
		string name, item, id, flag;
		int select;
		cin >> select;
		switch (select) {
			//��ѯ����
			case 1:
				L.selectAll();
				break;
			case 2:
				//��ӹ���
			{
				id = to_string(L.getTotal()+1);
				int n=id.size();
				for (int i = 0; i <= 4 - n; i++ ) {
					id = "0" + id;
				}
				cout << "����������:";
				cin >> name;
				cout << "����������:";
				cin >> item;
				Books b(id, name, item, true);
				L.add(&b);
			}
			break;
	
			case 3: {
				cout << "���������" << endl;
				cin >> id;
				if (L.remove(id)) {
					cout << "ɾ���ɹ�" << endl;
				} else {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
				}
			}
			break;
			case 4:
				//�޸Ĺ���
			{
				cout << "��������ţ�" ;
				cin >> id;
				Books* book = (Books*)L.selectById(id);
				if (book == NULL) {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
				} else {
					cout << "������";
					cin >> name;
					cout << "���";
					cin >> item;
					cout << "����״̬(Y/N):";
					cin >> flag;
					Books b(id, name, item, flag == "Y" ? true : false);
					L.modify(&b);
				}
			}
			break;
			case 5: {
				cout << "���������" << endl;
				cin >> id;
				Books* book = (Books*)L.selectById(id);
				if (book ==NULL) {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
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
���߹���ģ�飺
	����ɹ���:
		1�������򵥵��û����棬ÿ�β�������cls�����Ļ;
		2����������ɾ�Ĳ�(���÷����ѷ�װ��Readers����);
		3�����������������������������û�ǰ�����ж������û��������Ƿ�Ϸ�
**/
void readerManagment() {

}

//���ĵǼ�ģ��
void record(reader &user) {
	cout << user.toString();
}

