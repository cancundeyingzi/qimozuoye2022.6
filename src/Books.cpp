#include "Books.h"

Books::Books() {
}

Books::Books(string id, string name, string item, bool flag, bool del, string readerId): Base(id, name, del),
	item(item),
	flag(flag), readerId(readerId) {
}

void Books::setFlag(bool flag) {
	this->flag = flag;
}


string Books::getName() {
	return Base::getName();
}

string Books::getId() {
	return Base::getId();
}

string Books::getItem() {
	return item;
}

bool Books::getFlag() {
	return flag;
}

void Books::setDel(bool state) {
	Base::setDel(state);
}

bool Books::getDel() {
	return Base::getDel();
}

string Books::toString() {
	string f = flag ? "true" : "false";
	string d = Base::getDel() ? "true" : "false";
	return Base::toString() + item + "," + f + "," + d + "," + this->readerId + "\n";
}

void Books::setReaderId(string id) {
	this->readerId = id;
}

string Books::getReaderId() {
	return this->readerId;
}

Books::~Books() {
}