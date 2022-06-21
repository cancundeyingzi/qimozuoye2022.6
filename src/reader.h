#pragma once
#ifndef READER_H
#define READER_H
#include "Base.h"

class reader: public Base {
	private:
//		string name;
//		string id;
		string tel;
		string password;
		vector<string> books;

	public:
		reader();
		reader(string id, string name, string tel, string pwd);

		string getName();
		string getId();
		string getTel();
		string toString();
		string getPassword();
		bool check(string pwd);
		~reader();
};

#endif