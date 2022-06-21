#include "Readers.h"

vector<reader> &Readers::getReaders() {
	return this->readers;
}

void Readers::setReaders(vector<reader> &readers) {
	this->readers = readers;
}

bool Readers::add(Base *b) {
	int n = readers.size();
	readers.push_back(*(reader *)b);
	return n == readers.size() - 1;
}

bool Readers::remove(string id) {
	for (int i = 0; i < readers.size(); i++) {
		if (id == this->readers[i].getId()) {
			readers.erase(readers.begin() + i );
			return true;
		}
	}
	return false;
}

bool Readers::modify(Base *b) {
	reader *r = (reader *)b;
	string id = r->getId();
	for (int i = 0; i < readers.size(); i++) {
		if (id == this->readers[i].getId()) {
			readers[i] = *r;
			return true;
		}
	}
	return false;
}

Base *Readers::selectById(string id) {
	reader *r = NULL;
	for (int i = 0; i < readers.size(); i++) {
		if (id == this->readers[i].getId()) {
			r = &readers[i];
			break;
		}
	}
	//失败标志为NULL
	return r;
}

void Readers::selectAll() {
	cout << "====================================================" << endl;
	cout << "行号\t学号\t姓名\t\t电话" << endl;
	for (int i = 0; i < readers.size(); i++) {
		printf("%-5d\t%-8s%-15s%-15s\n", i, readers[i].getId().c_str(), readers[i].getName().c_str(),
		       readers[i].getTel().c_str() );
	}
	cout << "====================================================" << endl;
}

int Readers::getTotal() {
	return readers.size();
}