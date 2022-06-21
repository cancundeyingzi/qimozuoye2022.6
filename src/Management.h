#pragma once
#include <bits/stdc++.h>
#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include "Books.h"

class Management {
	public:
		virtual bool add(Base *b) = 0;
		virtual bool remove(string id) = 0;
		virtual bool modify(Base *b)  = 0;
		virtual Base *selectById(string id) = 0;
		virtual void selectAll()  = 0;
};

#endif

