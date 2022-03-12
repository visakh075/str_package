#include "lib_package.h"
#include <cstdio>
#include <cstdlib>
#include "lib_package.h"
size_t getfs(const char * url)
{
    FILE * fp=fopen(url,"r+b");
    if(fp!=NULL)
    {
        fseek(fp,0L,SEEK_END);
        size_t res=ftell(fp);
        fclose(fp);
        return(res);
    }
    return(0);
}
package::package(char * _path)
{
    
}
