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

//����У��
int mainSystem::input() {
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

//��¼ģ��
void mainSystem::Login() {
	system("cls");
	while (1) {
		cout << "____________________________________________________" << endl;
		cout << "||================================================||" << endl;
		cout << "||" << "\t\t    ͼ��ݹ���ϵͳ" << "\t\t  ||" << endl;
		cout << "||------------------------------------------------||" << endl;
		cout << "||    1-����Ա    2-�û�    3-ע���û�    0-�˳�  ||" << endl;
		cout << "||================================================||" << endl;
		cout << "����������������������������������������������������" << endl;
		int select;
		cout << "��ѡ����Ĳ�����";
		select = input();
		switch (select) {
			case 0:
				cout << "�˳��ɹ�";
				return;
			case 1: {
				//�������Ϊ����ʹ��Ĭ������
				if (password == "") {
					password = enCode("admin");
				}
				string pwd;
				cout << "���������Ա����:" ;
				cin >> pwd;
				if (enCode(pwd) == password) {
					cout << "��½�ɹ�" << endl;
					system("cls");
					administrators();
				} else {
					system("cls");
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
						system("cls");
						record(*user);
					} else {
						system("cls");
						cout << "��½ʧ��" << endl;
					}
				} else {
					system("cls");
					cout << "ѧ�Ų�����,����������" << endl;
				}
			}
			break;
			//ע��
			case 3: {
				string name, tel, pwd;
				cout << "������";
				cin >> name;
				cout << "���룺";
				cin >> pwd;
				cout << "�ֻ����룺";
				cin >> tel;
				//����id
				string id = R.buildId();
				reader r(id, name, tel, enCode(pwd));
				R.add(&r);
				system("cls");
				cout << "[��ʾ]ע��ɹ������μ����ѧ�ţ�" << r.getId() << endl;
				break;
			}
			default:
				system("cls");
				cout << "�����ܲ������뷵�أ�" << endl;
				break;
		}

	}

}

//д��ģ��
void mainSystem::writeDataToProperties() {
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

//��ȡģ��
void mainSystem::readDataFromProperties() {
//	cout << "[��ʾ]�����ʼ��......" << endl;
	//����������
	ifstream inf_book("config\\library.dat", ios::in);
	ifstream inf_reader("config\\readers.dat", ios::in);
	fstream inf("config\\key.dat");
	ifstream inf_record("config\\records.dat", ios::in);
	//��������
//	cout << "[��ʾ]�����Ѵ���......" << endl;
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
				records.push_back(Record(s[0], s[1], s[2], s[3],  s[5] == "����" ? false : true, s[4]));
				recordNum++;
			}
		}
	}
//	cout << "[��ʾ]����ȡ�鼮��¼" << bookNum << "��" << ",";
//	cout << "���߼�¼" << readerNum << "��" << endl;
//	L.selectAll();
//	R.selectAll();
//	cout << "[��ʾ]�����ʼ����ɣ�\n";
	inf.close();
	inf_book.close();
	inf_reader.close();
}

//������
void mainSystem::administrators() {
	while (1) {
		system("cls");
		cout << "__________________________________________________________________________" << endl;
		cout << "||======================================================================||" << endl;
		cout << "||" << "                           ��ӭ�������Աϵͳ                         ||" << endl;
		cout << "||======================================================================||" << endl;
		cout << "||" << "    1-ͼ�����  2-���߹���  3-�޸�����  4-��ѯ���ļ�¼  0-�˳�        ||" << endl;
		cout << "||======================================================================||" << endl;
		cout << "��������������������������������������������������������������������������" << endl;
		int select = input();
		switch (select) {
			case 0:
				system("cls");
				cout << "�˳��ɹ�";
				return;
			case 1:
				bookManagment();
				break;
			case 2:
				readerManagment();
				break;
			case 3: {
				cout << "������ԭ����:";
				string pwd, newPwd;
				cin >> pwd;
				if (enCode(pwd)  == password) {
					cout << "������������";
					cin >> newPwd;
					password = enCode(newPwd);
					writeDataToProperties();
				} else {
					cout << "��������볢�ԣ�" << endl;
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
				cout << "��������������������������������������������������������������������������������" << endl;
				system("pause");
				break;
			default:
				system("cls");
				cout << "�����ܲ������뷵�أ�" << endl;
				break;
		}
	}
}

void mainSystem::bookManagment() {
	while (1) {
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
				//���������ID
				id = L.buildId();
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
				if (!((Books *)L.selectById(id))->getFlag()) {
					//�����ߵ����Ӧ��˵��
					cout << "�Ȿ�鱻������" << endl;
					break;
				}
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
				} else if (!book->getFlag()) {
					//�����ߵ����Ӧ��˵��
					cout << "�Ȿ�鱻������" << endl;
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
			default:
				system("cls");
				cout << "�����ܲ������뷵�أ�" << endl;
				break;
		}
		cout << "�����������";
		getchar();
		getchar();
	}
}

void mainSystem::readerManagment() {
	while (1) {
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
				id = R.buildId();
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
			default:
				system("cls");
				cout << "�����ܲ������뷵�أ�" << endl;
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
		printf("%-10s%-30s%-15s%10s\n", "||���", "    ����", "  ����", "    �Ƿ񱻽���||");
		for (int i = 0; i < books.size(); i++) {
			if (books[i].getReaderId() == user.getId()) {
				arr++;
				printf("||%-10s%-30s%-15s%8s\n", books[i].getId().c_str(), books[i].getName().c_str(), books[i].getItem().c_str(),
				       "      ��    ||");
			}
		}
		cout << "||===================================================================||" << endl;
		cout << "||��ѡ�����Ĳ���   1.����   2.����   3.�޸�����   4.�˳�����         ||" << endl;
		cout << "||===================================================================||" << endl;
		string t;
		cout << "��ѡ����Ĳ���:";
		cin >> t;
		if (t == "1") {
			system("cls");
			cout << "(�����밴9)��ǰͼ���ͼ�����£�" << endl;
			L.selectAll();

			do {
				cout << "(�����밴9)���������������ID:";
				cin >> id;
				book = (Books *)L.selectById(id);
				if ( id == "9") {
					system("cls");
					break;
				} else if (book == NULL) {
					cout << "�������Ȿ��,�����²�ѯ" << endl;
				} else if (book->getFlag() == false ) {
					cout << "�Ȿ���ѱ�����" << endl;
				} else {
					arr++;
					book->setReaderId(user.getId());
					book->setFlag(false);
					L.modify(book);
					system("cls");
					cout << "����ɹ�" << endl;
					Record J(book->getReaderId(), book->getName(), user.getId(), user.getName(), false); //����
					J.toString();
					records.push_back(J);
					writeDataToProperties();
					break;
				}
			} while (1);
		} else if (t == "2") {
			if (arr == 0) {
				cout << "���û�δ���������������" << endl ;
			} else {
				do {
					cout << "(�����밴9)��������Ҫ�黹���ID:" ;
					cin >> id;
					book = (Books *)L.selectById(id);
					if (id == "9") {
						system("cls");
						break;
					} else if (book == NULL) {
						cout << "�������" << endl;
					} else if (book->getReaderId() == user.getId()) {
						book->setReaderId("null");
						book->setFlag(true);
						L.modify(book);
						system("cls");
						cout << "����ɹ�" << endl;
						Record J(book->getReaderId(), book->getName(), user.getId(), user.getName(), true);
						J.toString();
						records.push_back(J);
						writeDataToProperties();
						break;
					} else {
						cout << "����δ���Ĵ���" << endl;;
					}
				} while (1);
			}
		} else if (t == "3") {
			cout << "��������ľ�����:";
			cin >> j_pwd;
			if (user.getPassword() == enCode(j_pwd)) {
				cout << "���������������:";
				cin  >> x_pwd;
				user.setPwd(enCode(x_pwd));
				R.modify(&user);
				writeDataToProperties();
				system("cls");
				cout << "�޸ĳɹ�";
			} else {
				system("cls");
				cout << "��������󷵻�" << endl;
			}
		} else if (t == "4") {
			cout << "�˳��ɹ�" << endl;
			break;
		} else {
			system("cls");
			cout << "���޴˲������밴��ʾ����" << endl;
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