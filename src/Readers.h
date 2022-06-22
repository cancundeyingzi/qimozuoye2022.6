#pragma once
#ifndef READERS_H
#define READERS_H
#include "reader.h"
#include "Management.h"

class Readers: public Management {
	private:
		vector<reader> readers;
	public:
		vector<reader> &getReaders();
		void setReaders(vector<reader> &readers);


		bool add(Base *b);
		bool remove(string id);
		bool modify(Base *b);
		Base *selectById(string id);
		void selectAll();

		int getTotal();

};

#endif