#pragma once
#ifndef RECORD_H
#define RECORD_H

#include "Base.h"
#include <time.h>
using namespace std;

class Record : public Base {
		string bookName;
		string bookId;
		string readerName;
		string readerId;
		string date;
		bool action;
	public:
		Record();
		Record( string bookId, string bookName, string readerId, string readerName,  bool action);

		string getBookName();
		string getBookId();
		string getReaderName();
		string getReaderId();
		string getDate();
		bool getAction();
		void toString();
	protected:
};

#endif