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
	strlist tag_list;
	int tag_list_len;
	void map(int from,int to,int p);
	// maped functions
	void search(char *);
	int compare(uint idx1,uint idx2);
	void show();

};
typedef class c_package package;