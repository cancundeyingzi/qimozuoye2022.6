#include "reader.h"

reader::reader() {
}

reader::reader(string id, string name, string tel, string pwd, bool del): Base(id, name, del), tel(tel),
	password(pwd) {
}

string reader::getName() {
	return Base::getName();
}

string reader::getId() {
	return Base::getId();
}

string reader::getTel() {
	return this->tel;
}

string reader::toString() {
	string d = Base::getDel() ? "true" : "false";
	return Base::toString() + tel + "," + password + "," + d + "\n";
}

bool reader::check(string pwd) {
	return pwd == password;
}

string reader::getPassword() {
	return password;
}

void reader::setDel(bool state) {
	Base::setDel(state);
}

bool reader::getDel() {
	return Base::getDel();
}

reader::~reader() {
}