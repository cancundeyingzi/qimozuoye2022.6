#include "Record.h"

Record::Record() {
	size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm * timeptr);
	time_t timer = time(NULL);
	char szbuf[256] = {0};
	strftime(szbuf, sizeof(szbuf), "%Y-%m-%d %H:%M:%S", localtime(&timer));
	this->date = szbuf;
}
Record::Record( string bookId, string bookName, string readerId, string readerName,  bool action): bookName(bookName),
	bookId(bookId),

	readerName(readerName), readerId(readerId), action(action) {
	size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm * timeptr);
	time_t timer = time(NULL);
	char szbuf[256] = {0};
	strftime(szbuf, sizeof(szbuf), "%Y-%m-%d %H:%M:%S", localtime(&timer));
	this->date = szbuf;
}

string Record::getBookName() {
	return this->bookName;
}

string Record::getBookId() {
	return this->bookId;
}

string Record::getReaderName() {
	return this->readerName;
}

string Record::getReaderId() {
	return this->readerName;
}

string Record::getDate() {
	return this->date;
}

bool Record::getAction() {
	return this->action;
}

void Record::toString() {
	string str = action ? "ªπ È" : "ΩË È";
	printf("%-10s%-15s%-10s%-15s%-20s%-5s\n", bookId.c_str(), bookName.c_str(), readerId.c_str(), readerName.c_str(),
	       date.c_str(), str.c_str());
}