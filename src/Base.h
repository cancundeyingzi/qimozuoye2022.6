#pragma once
#include <bits/stdc++.h>
#ifndef BASE_H
#define BASE_H
using namespace std;

class Base {
	private:
		string id;
		string name;
		bool del;
	public:
		Base();
		Base(string id, string name, bool del = false);
		void setDel(bool state);
		bool getDel();
		string getName();
		string getId();
		string toString();
		~Base();
};

#endif

