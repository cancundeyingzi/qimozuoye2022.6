#include "reader.h"

reader::reader() {
}

reader::reader(string id, string name, string tel, string pwd): Base(id, name), tel(tel), password(pwd) {
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
	return Base::toString() + this->tel + "," + this->password + "\n";
}

bool reader::check(string pwd) {
	return pwd == password;
}

string reader::getPassword() {
	return password;
}

reader::~reader() {
}