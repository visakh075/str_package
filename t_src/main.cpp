#include "lib_strlist.h"
#include "lib_package.h"
#include <stdbool.h>
int main()
{
    // const char * file="/Users/erkattiri/Desktop/Lab/str_package/test_file.txt";
    // const char * file="/Users/erkattiri/Desktop/Lab/str_package/MyECU.ecuc.arxml.txt";
    
    const char * file="/Users/erkattiri/Desktop/Lab/str_package/visakh.html";

    printf("%lu\n",getfs(file));
    package str_pack=package((char*)file);
    // str_pack.packet_list.show();


    // printf("\n/ActiveEcuC/ComM : %u(%u) ECUC-REFERENCE-VALUE : %u(%u)\n",strhash("/ActiveEcuC/ComM"),strlen_s("/ActiveEcuC/ComM"),strhash("ECUC-REFERENCE-VALUE"),strlen_s("ECUC-REFERENCE-VALUE"));
    // str_pack.search("ECUC-REFERENCE-VALUE");
    // for(uint x=0;x<str_pack.tag_list.len;x++)
    // {
    //     for(uint y=0;y<str_pack.tag_list.len;y++)
    //     {
    //         // if(str_pack.compare(x,y)==true)
    //         // {
    //         //     // printf("(%d,%d)",x,y);
    //         // }
    //     }
    // }
    return 0;
}