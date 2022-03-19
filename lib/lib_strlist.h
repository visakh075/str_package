/*
    SPECIAL STRLIST WITH TWO ADDITIONAL DATA POINTS FOR PACKAGING
    FLAG AND PATH
    add an intiger array to hold the checksome list


    Search list
    search by index
     build a compare function which will compare the check sums
*/
#ifndef __STRLIST__
#define __STRLIST__

#define LOG_ENSY 1
#define LOG_BUFF_SZ 100
#define LOG_FILE "strlist_map.log"
//  DEBUG >>
    #include "lib_rtlog.h"
    #if(LOG_ENSY==1)
        extern rtlog map;
        extern char buff[LOG_BUFF_SZ];
        #define LOG() map << buff
        // Wrappper
        #define LOG_STR(x) ({map<<x;})
        #define LOG_ITM_INIT() {\
            sprintf(buff,"item * : %p %p",this,loc);\
            map<<buff;\
        }
        #define LOG_ITM_SET() {\
            sprintf(buff,"item < : %p %p %s",this,loc,loc);\
            map<<buff;\
        }
        #define LOG_ITM_PROBE() {\
            sprintf(buff,"\nitem > : %p %p %3ld %6ld  %s ",this,loc,flag,path,loc);\
            map<<buff;\
            sprintf(buff,"chksum :");map+buff;\
            for(uint i=0;i<chksum.len;i++){sprintf(buff," %u",chksum.list[i]);map+buff;}\
        }
        #define LOG_ITM_DEST() {\
            sprintf(buff,"item ~ : %p %p %3ld %6ld  %s ",this,loc,flag,path,loc);\
            map<<buff;\
        }
    #else
        #define LOG()
        // Wrappper
        
        #define LOG_STR(x)
        #define LOG_ITM_INIT()
        #define LOG_ITM_SET()
        #define LOG_ITM_PROBE()
        #define LOG_ITM_DEST()

    #endif
//  DEBUG <<

typedef unsigned int uint;

typedef struct
{
    uint * list;
    uint len;
    uint head_end;
} s_chksum_list;
typedef struct
{
    uint sum;
    uint len;
} s_chksum;
class item_c{
	public:
		char * loc;
		uint len;
        s_chksum_list chksum;
        void crunch();
        long int flag,path;
		item_c *in ,*out;
		item_c();
		item_c(const char *);
		~item_c();
		void set(const char *);
		void reset(const char *);
		void probe();
		void con_tail(item_c *);
		void con_head(item_c *);
		item_c* push(const char *);
		void operator = (const char *);
};
typedef class item_c item;
typedef struct
{
    item ** list;
    uint len;
}search_list;
class strlist_c{
	public:
		item_c * head ,* tail;
		uint len;
		strlist_c();
		~strlist_c();
		void push(const char *);
		void probe();
		void show();
		item_c * get(uint index);
		item_c * getI(uint index);
		item_c * operator [] (uint index);
        void search(char *);
        int compare(uint idx1,uint idx2);    
};
typedef class strlist_c strlist; 
uint strlen(const char *);
s_chksum get_chksum(char * str);
uint strlen_s(char * strptr);

#endif
