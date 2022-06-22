#include <iostream>
#include "Library.h"
#include "Readers.h"
#include "reader.h"
#include "Books.h"
#include "Record.h"
using namespace std;
void Login();//��¼ģ��
void writeDataToProperties();//д��ģ��
void readDataFromProperties();//��ȡģ��
void init();//��ʼ��
void administrators();//������
void bookManagment();//ͼ�����ģ��
void readerManagment();//���߹���ģ��
void record(reader &user);//���黹��ģ��
string enCode(string key);//MD5����
Library L;//ͼ�������
Readers R;//���߹�����
vector<Record> records;//���黹���¼
string password = ""; //����Ա����

void toContinue() {
	cout << "�����������";
	getchar();
	system("cls");
}

int main() {
	init();
}

//��ʼ��-����
void init() {
	//��ȡ����
	readDataFromProperties();
	toContinue();
	Login();
}

int input() {
	int select;
	cin >> select;
	while (cin.fail()) { //����������ͺͶ������Ͳ�һ��Ϊtrue
		if (cin.fail()) {
			cout << "����ѡ��Ϸ�������" << endl;
			cin.clear();
			cout << "����������" << endl;
			while (cin.get() != '\n') {
				continue;
			}
			cin >> select;
		}
	}
	return select;
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
	reader r(id, name, tel, enCode(pwd));
	R.add(&r);
	cout << "[��ʾ]ע��ɹ������μ����ѧ�ţ�" << r.getId() << endl;
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
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||" << "\t\t    ͼ��ݹ���ϵͳ" << "\t\t  ||" << endl;
		cout << "||------------------------------------------------||" << endl;
		cout << "||��ѡ�������� 1-����Ա 2-�û� 3-ע���û� 0-�˳�||" << endl;
		cout << "||================================================||" << endl;
		cout << "����������������������������������������������������" << endl;
		int select;
		select = input();
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
				if (user != NULL) {
					if (user->check(enCode(pwd))) {
						record(*user);
					} else {
						cout << "��½ʧ��" << endl;
					}
				} else {
					cout << "ѧ�Ų�����,����������" << endl;
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

	while (1) {
		system("cls");
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||" << "\t\t ��ӭ�������Աϵͳ" << "\t\t  ||" << endl;
		cout << "||------------------------------------------------||" << endl;
		cout << "||" << "\t1-ͼ�����\t2-���߹���\t0-�˳�" << "\t  ||" << endl;
		cout << "||================================================||" << endl;
		cout << "����������������������������������������������������" << endl;
		int select = input();
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
	cout << "[��ʾ]�����ʼ��......" << endl;
	//����������
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	ifstream inf_record("config\\records.dat", ios::in);
	//��������
	cout << "[��ʾ]�����Ѵ���......" << endl;
	vector<Books> book;
	vector<reader> readers;
	int bookNum = 0, readerNum = 0, recordNum = 0;
	//�ļ��쳣����

	if (inf) {
		inf >> password;
	} else {
		cout << "[����]�ļ�:config\\key.dat������" << endl;
	}
	if (!inf_book) {
		cout << "[����]�ļ�:config\\library.dat������" << endl;
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
		cout << "[����]�ļ�:config\\readers.dat������" << endl;
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
		cout << "[����]�ļ�:config\\records.dat������" << endl;;
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
				records.push_back(Record(s[0], s[1], s[2], s[3],  s[5] == "f" ? false : true, s[4]));
				recordNum++;
			}
		}
	}
	cout << "[��ʾ]����ȡ�鼮��¼" << bookNum << "��" << ",";
	cout << "���߼�¼" << readerNum << "��" << endl;
	L.selectAll();
	R.selectAll();
	cout << "[��ʾ]�����ʼ����ɣ�";
	inf.close();
	inf_book.close();
	inf_reader.close();
}

//һ����������
void writeDataToProperties() {
	cout << "[��ʾ]�Զ�����..." << endl;
	//��ȡ�ڴ��е�����
	vector<Books> book = L.getBooks();
	vector<reader> readers = R.getReaders();
	//����������
	ofstream outf_book("config\\library.dat", ios:: out);
	ofstream outf_reader("config\\readers.dat", ios:: out );
	ofstream outf_key("config\\key.dat", ios::out);
	ofstream outf_record("config\\records.dat", ios::out);
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

	val = "";
	for (int i = 0; i < records.size(); i++) {
		val += records[i].Out();
	}
	outf_record << val;
	//��������
	if (password != "") {
		//����
		outf_key << password.c_str();
	}

	outf_record.close();
	outf_reader.close();
	outf_book.close();
	outf_key.close();
}

string enCode(string key) {
	string result;
	string md(string key);
	result = md(key);
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
	system("cls");
	cout << "____________________________________________________" << endl;
	cout << "||================================================||" << endl;
	cout << "||\t\t    " << "1-��ѯ����ͼ��" << "\t\t  ||" << endl;
	cout << "||\t\t    " << "2-����ͼ��" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "3-ɾ��ͼ��" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "4-�޸�ͼ��" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "5-��ѯͼ��" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "6-�˳�" << "\t\t\t  ||" << endl;
	cout << "||================================================||" << endl;
	cout << "����������������������������������������������������" << endl;
}

void bookManagment() {
	while (1) {
		BookMsg();
		string name, item, id, flag;
		int select = input();
		system("cls");
		switch (select) {
			//��ѯ����
			case 1:
				L.selectAll();
				break;
			case 2:
				//��ӹ���
			{
				id = to_string(L.getTotal() + 1);
				int n = id.size();
				for (int i = 0; i <= 4 - n; i++ ) {
					id = "0" + id;
				}
				cout << "����������:";
				cin >> name;
				cout << "����������:";
				cin >> item;
				Books b(id, name, item, true);
				L.add(&b);
				writeDataToProperties();
			}
			break;

			case 3: {
				L.selectAll();
				cout << "���������" << endl;
				cin >> id;
				if (L.remove(id)) {
					cout << "ɾ���ɹ�" << endl;
					writeDataToProperties();
				} else {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
				}
			}
			break;
			case 4:
				//�޸Ĺ���
			{
				L.selectAll();
				cout << "��������ţ�" ;
				cin >> id;
				Books *book = (Books *)L.selectById(id);
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
					writeDataToProperties();
				}
			}
			break;
			case 5: {
				L.selectAll();
				cout << "���������" << endl;
				cin >> id;
				Books *book = (Books *)L.selectById(id);
				if (book == NULL) {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
				} else {
					cout << book->toString();
				}
			}
			break;
			case 6:
				return;
				break;
		}
		cout << "�����������";
		getchar();
		getchar();
	}
}


/**
���߹���ģ�飺
	����ɹ���:
		1�������򵥵��û����棬ÿ�β�������cls�����Ļ;
		2����������ɾ�Ĳ�(���÷����ѷ�װ��Readers����);
		3�����������������������������û�ǰ�����ж������û��������Ƿ�Ϸ�
**/
void readerMsg() {
	system("cls");
	cout << "____________________________________________________" << endl;
	cout << "||================================================||" << endl;
	cout << "||\t\t    " << "1-��ѯ���ж���" << "\t\t  ||" << endl;
	cout << "||\t\t    " << "2-��������" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "3-ɾ������" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "4-�޸Ķ���" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "5-��ѯ����" << "\t\t\t  ||" << endl;
	cout << "||\t\t    " << "6-�˳�    " << "\t\t\t  ||" << endl;
	cout << "||================================================||" << endl;
	cout << "����������������������������������������������������" << endl;
}

void readerManagment() {
	while (1) {
		readerMsg();
		string name, tel, id;
		int select = input();
		system("cls");
		switch (select) {
			//��ѯ����
			case 1:
				R.selectAll();
				break;
			case 2:
				//��ӹ���
			{
				id = to_string(R.getTotal() + 1);
				int n = id.size();
				for (int i = 0; i <= 4 - n; i++ ) {
					id = "0" + id;
				}
				cout << "����������:";
				cin >> name;
				cout << "�������ֻ�����:";
				cin >> tel;
				reader r(id, name, tel, "");
				R.add(&r);
				writeDataToProperties();
			}
			break;

			case 3: {
				R.selectAll();
				cout << "������ѧ��" << endl;
				cin >> id;
				if (R.remove(id)) {
					cout << "ɾ���ɹ�" << endl;
				} else {
					cout << "�����ڴ���,�����²�ѯ" << endl;
					writeDataToProperties();
				}
			}
			break;
			case 4:
				//�޸Ĺ���
			{
				R.selectAll();
				cout << "������ѧ�ţ�" ;
				cin >> id;
				reader *r = (reader *)R.selectById(id);
				if (r == NULL) {
					cout << "�����ڴ���,�����²�ѯ" << endl;
				} else {
					cout << "������";
					cin >> name;
					cout << "�ֻ��ţ�";
					cin >> tel;
					reader reader(id, name, tel, r->getPassword());
					R.modify(&reader);
					writeDataToProperties();
				}
			}
			break;
			case 5: {
				R.selectAll();
				cout << "������ѧ��" << endl;
				cin >> id;
				reader *r = (reader *)R.selectById(id);
				if (r == NULL) {
					cout << "�����ڴ���,�����²�ѯ" << endl;
				} else {
					cout << r->toString();
				}
			}
			break;
			case 6:
				return;
				break;
		}
		cout << "�����������";
		getchar();
		getchar();
	}
}



//���ĵǼ�ģ��
void record(reader &user) {
	cout << "����" << endl;
	string id;
	while (1) {
		cout << "��ѡ�����Ĳ��� 1.���� 2.���� 3.�鿴��ǰ������� 4.�޸����� 5.�˳�����" << endl;
		string t;
		cin >> t;
		if (t == "1") {
			Books *book ;
			cout << "��ǰͼ���ͼ�����£�" << endl;
			L.selectAll();
			cout << "�Ƿ�������Ҫ���ĵ�ͼ��(y/n)" << endl;
			string s;
			cin >> s;
			if (s == "y") {
				do {
					cout << "���������������ID:";
					cin >> id;
					book = (Books *)L.selectById(id);
					if (book == NULL ) {
						cout << "�������Ȿ��,�����²�ѯ" << endl;
					} else {
						book->setReaderId(user.getId());
						book->setFlag(true);
						L.modify(book);
						cout << "����ɹ�" << endl;
						Record J(book->getReaderId(), book->getName(), user.getId(), user.getName(), false); //����
						J.toString();
						records.push_back(J);
						writeDataToProperties();
						break;

					}
				} while (1);

				//���д�������
			}
		} else if (t == "2") {
//   } else {
//    cout << "��������Ҫ�黹������:" << endl;
//    string bookName;
//    cin >> bookName;
//    if {
//     cout << "����ɹ�" << endl;
//    } else {
//     cout << "����δ���Ĵ���" << endl;
//    }
//   }
		} else if (t == "3") {
		}  else if (t == "4") {
			cout << "�˳��ɹ�" << endl;
			break;
		} else {
			cout << "���޴˲������밴��ʾ����" << endl;
		}
	}

	getchar();
}
