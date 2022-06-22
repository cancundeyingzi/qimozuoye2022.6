#ifndef BOOKS_H
#define BOOKS_H
#pragma once
#include <string>
#include "Base.h"
using namespace std;

class Books : public Base {
	private:
//		string name;
//		string id;
		string item;
		bool flag;
		string readerId;//½èÔÄÕßµÄID
	public:
		Books();
		Books(string id, string name, string item, bool flag, bool del = false, string readerId = "null");
		void setFlag(bool flag);
		void setDel(bool state);
		string getName();
		string getId();
		string getItem();
		bool getFlag();
		bool getDel();
		string toString();
		void setReaderId(string id);
		string getReaderId();
		~Books();
};

#endif