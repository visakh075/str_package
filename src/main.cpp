#include "lib_strlist.h"
#include "lib_package.h"
int main()
{
    // const char * file="/test.txt";
    const char * file="/Users/erkattiri/Desktop/Lab/str_package/bin/test.txt";
    printf("%lu",getfs(file));
    return 0;
}