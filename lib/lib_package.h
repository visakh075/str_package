#pragma once
#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
typedef unsigned char bytes;
size_t getfs(const char * filename);
class c_package{
	public:
	c_package(char *);
	void read(char *);
	strlist packet_list;
	int tag_list_count=0;
	void map(int from,int to,int p);

};
typedef class c_package package;