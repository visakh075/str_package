#pragma once
#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
typedef unsigned char bytes;
size_t getfs(char * filename);
class package{
	public:
	package(char *);
	void read();
	strlist packet_list;
	int tag_list_count=0;

};