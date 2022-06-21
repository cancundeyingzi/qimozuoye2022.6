#include "Books.h"

Books::Books() {
}

Books::Books(string id, string name, string item, bool flag): Base(id, name), item(item), flag(flag) {
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

string Books::toString() {
	string f = flag ? "true" : "false";
	return Base::toString() + item + "," + f + "\n";
}

Books::~Books() {
}