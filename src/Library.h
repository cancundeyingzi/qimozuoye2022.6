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
		//根据Id设置图书的借阅状态
		void setFlag(string id, bool start);
		void setBooks(vector<Books> &books);
		//添加,已完成
		bool add(Base *b);
		//删除,已完成
		bool remove(string id);
		//修改,配合selectById使用,已完成
		bool modify(Base *b);
		//按Id查询 已完成
		Base *selectById(string id);
		//查询所有 已完成
		void selectAll();
		//返回总数
		int getTotal();
		vector<Books> &getBooks();
		~Library();
};

#endif

