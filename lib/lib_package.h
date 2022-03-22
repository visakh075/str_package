#pragma once
#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
#include <inttypes.h>
typedef unsigned char bytes;
typedef long int lint;
typedef uint32_t u32;
size_t getfs(const char * filename);
typedef class que_c
{
	public:
    item ** list;
    u32 len;
    item * last;

	que_c();
	~que_c();

	void push(item* ptr);
	void pop();
	void show();

}que_c;

class c_package{
	public:
	c_package(char *);
	void read(char *);
	strlist tag_list;
	u32 tag_list_len;
	void map();
	// maped functions
	void search(char *);
	bool compare(u32 idx1,u32 idx2);
	void show();

	private:
	que_c que;

	// status
	uint cmp;

};
typedef class c_package package;