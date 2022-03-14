#ifndef __LIB_STR_PACK__
#define __LIB_STR_PACK__
#include <cstdio>
class package
{
    public:
    package(char *);
    ~package();
    char * path;

};
size_t getfs(const char *);
#endif