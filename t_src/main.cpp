#include "lib_strlist.h"
#include "lib_package.h"
int main()
{
    // const char * file="/Users/erkattiri/Desktop/Lab/str_package/test_file.txt";
    const char * file="/Users/erkattiri/Desktop/Lab/str_package/MyECU.ecuc.arxml.txt";
    
    printf("%lu\n",getfs(file));
    package str_pack=package((char*)file);
    // str_pack.packet_list.show();


    printf("\n/ActiveEcuC/ComM : %u(%u) ECUC-REFERENCE-VALUE : %u(%u)\n",strhash("/ActiveEcuC/ComM"),strlen_s("/ActiveEcuC/ComM"),strhash("ECUC-REFERENCE-VALUE"),strlen_s("ECUC-REFERENCE-VALUE"));
    str_pack.packet_list.search("ECUC-REFERENCE-VALUE");
    for(uint x=str_pack.packet_list.ListCount-10;x<str_pack.packet_list.ListCount;x++)
    {
        for(uint y=str_pack.packet_list.ListCount-10;y<str_pack.packet_list.ListCount;y++)
        {
            printf("\n%s to %s -> %d",str_pack.packet_list.get(x)->loc,str_pack.packet_list.get(y)->loc,str_pack.packet_list.compare(x,y));
        }
    }
    return 0;
}