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
		Base(string id, string name, bool del = false): id(id), name(name), del(del) {
		}
		void setDel(bool state) {
			del = state;
		}
		bool getDel() {
			return del;
		}
		string getName() {
			return name;
		}
		string getId() {
			return id;
		}
		string toString();
		~Base();
};

#endif

