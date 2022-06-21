#pragma once
#ifndef LIBRARYIMPL_H
#define LIBRARYIMPL_H
#include "Management.h"
#include <vector>
#include "Books.h"
class Base;

class Library : public Management {
	private:
		vector<Books> books;
	public:
		Library();
		//����Id����ͼ��Ľ���״̬
		void setFlag(string id, bool start);
		void setBooks(vector<Books> &books);
		//���,�����
		bool add(Base *b);
		//ɾ��,�����
		bool remove(string id);
		//�޸�,���selectByIdʹ��,�����
		bool modify(Base *b);
		//��Id��ѯ �����
		Base *selectById(string id);
		//��ѯ���� �����
		void selectAll();
		//��������
		int getTotal();
		vector<Books> &getBooks();
		~Library();
};

#endif

