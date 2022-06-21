#include "main.cpp"
extern Library L;//ͼ�������
extern Readers R;//���߹�����

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
	try {
		if (!inf) {
			throw 1;
		}
		inf >> password;
	} catch (int) {
		cout << "�ļ�:config\\key.dat������" << endl;
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
			//�ֱ���� id ,name ,type ,flag
			if (s[0] != "" && s[1] != "" && s[2] != "" && s[3] != "") {
				book.push_back(Books(s[0], s[1], s[2], s[3][0] == 'f' ? true : false));
			}
		}
	} catch (int) {
		cout << "�ļ�:config\\library.dat������" << endl;
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
			//�ֱ���� id ,name ,tel
			if (s[0] != "" && s[1] != "" && s[2] != "") {
				readers.push_back(reader(s[0], s[1], s[2]));
			}
		}
	} catch (int) {
		cout << "�ļ�:config\\readers.dat������" << endl;
	}



//	if (inf) {
//		inf >> password;
//	} else {
//		cout << "�ļ�:config\\key.dat������" << endl;
//	}
//	if (!inf_book) {
//		cout << "�ļ�:config\\library.dat������" << endl;;
//	}
//
//	if (!inf_reader) {
//		cout << "�ļ�:config\\readers.dat������" << endl;
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