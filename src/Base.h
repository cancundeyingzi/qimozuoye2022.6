#pragma once
#include <bits/stdc++.h>
#ifndef BASE_H
#define BASE_H
using namespace std;

class Base {
	private:
		string id;
		string name;
	public:
		Base();
		Base(string id, string name): id(id), name(name) {
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

