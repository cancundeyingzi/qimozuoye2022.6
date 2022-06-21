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
	public:
		Books();
		Books(string id, string name, string item, bool flag);
		void setFlag(bool flag);
		string getName();
		string getId();
		string getItem();
		bool getFlag();
		string toString();
		~Books();
};

#endif