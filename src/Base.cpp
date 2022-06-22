#include "Base.h"

Base::Base() {

}

Base::Base(string id, string name, bool del): id(id), name(name), del(del) {
}

void Base::setDel(bool state) {
	del = state;
}

bool Base::getDel() {
	return del;
}

string Base::getName() {
	return name;
}

string Base:: getId() {
	return id;
}

string Base::toString() {
	return id + "," + name + ",";
}

Base::~Base() {
}