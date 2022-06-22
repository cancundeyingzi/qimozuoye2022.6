#include "Record.h"

Record::Record() {
	size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm * timeptr);
	time_t timer = time(NULL);
	char szbuf[256] = {0};
	strftime(szbuf, sizeof(szbuf), "%Y-%m-%d %H:%M:%S", localtime(&timer));
	this->date = szbuf;
}
Record::Record( string bookId, string bookName, string readerId, string readerName,
                bool action, string cur_date): bookName(bookName),
	bookId(bookId),

	readerName(readerName), readerId(readerId), action(action) {
	if (cur_date == "") {
		size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm * timeptr);
		time_t timer = time(NULL);
		char szbuf[256] = {0};
		strftime(szbuf, sizeof(szbuf), "%Y-%m-%d %H:%M:%S", localtime(&timer));
		this->date = szbuf;
	} else {
		this->date = cur_date;
	}
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

string Record::Out() {
	string str = action ? "还书" : "借书";
	return bookId+ "," + bookName.c_str() + "," + readerId.c_str() + "," + readerName.c_str() + "," +
	       date.c_str() + "," + str.c_str() + "\n";
}

void Record::toString() {
	string str = action ? "还书" : "借书";
	printf("%-10s%-15s%-10s%-15s%-20s%-5s\n", bookId.c_str(), bookName.c_str(), readerId.c_str(), readerName.c_str(),
	       date.c_str(), str.c_str());
}