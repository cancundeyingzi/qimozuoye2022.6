#include <iostream>
#include "Library.h"
#include "Readers.h"
#include "reader.h"
#include "Books.h"
#include "Record.h"

class mainSystem {
	private:
		Library L;//ͼ�������
		Readers R;//���߹�����
		vector<Record> records;//���黹���¼
		string password; //����Ա����
	public:
		mainSystem();
		void init();
		int input();
		void run();
		void Login();//��¼ģ��
		void writeDataToProperties();//д��ģ��
		void readDataFromProperties();//��ȡģ��
		void administrators();//������
		void bookManagment();//ͼ�����ģ��
		void readerManagment();//���߹���ģ��
		void record(reader &user);//���黹��ģ��
		string enCode(string key);//MD5����

};
