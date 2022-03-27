#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
#include "lib_rtlog.h"
#include "lib_package.h"
#if(LOG_ENSY==1)
rtlog que_map=rtlog("que_map.log",NORMAL);
char que_buff_t[LOG_BUFF_SZ];
	#define Q_LOG() que_map << que_buff_t
	// Wrappper
	#define Q_LOG_STR(x) ({que_map<<x;})
	#define Q_LOG_PUSH() {\
		sprintf(que_buff_t,"que * : %d %s",len-1,last->loc);\
		que_map<<que_buff_t;\
	}
	#define Q_LOG_ITM_DEST() {\
		sprintf(que_buff_t,"que > : %d %s",len-1,last->loc);\
		que_map<<que_buff_t;\
	}	
#else
	#define Q_LOG()
	#define Q_LOG_STR(x)
	#define Q_LOG_ITM_DEST()
	
#endif
size_t getfs(const char *filename){
	FILE *fp;
	fp=fopen(filename,"rb");
	if(fp!=NULL){
		fseek(fp, 0L, SEEK_END); 
		size_t res = ftell(fp);
		fclose(fp);return(res);}
	return(0);}
c_package::c_package(char * url)
{
	tag_list_len=0;
	read(url);
}
void c_package::read(char * url){
	
	FILE *handler = fopen(url,"r+b");
	long temp_len=1;
	char s;
	char *temp_word=(char *)malloc(sizeof(char));
	char t_s='t';
	pos position;
	position.line=1;
	position.col=0;
	while(!feof(handler))
	{   
		s=fgetc(handler);
		
		switch(s)
		{
			case '<':
			case '>':
				
				if(temp_len>1)
				{					
					tag_list.push((const char *)temp_word);
					
					tag_list.getI(0)->flag=(temp_word[temp_len-2]=='/')?'v' : t_s;
					tag_list.getI(0)->path=-1;
					tag_list.getI(0)->position=position;
					tag_list.getI(0)->position.col=position.col-temp_len;
					
					tag_list_len++;
					temp_len=1;
					free(temp_word);
					temp_word=NULL;
					temp_word=(char *)malloc(sizeof(char));
					
				}
				t_s=(s=='>') ? 'v':'t';
				position.col++;
				break;
			
			case '\n':position.line++;position.col=0;
			case '\r':
				continue;
				break;
			case ' ':if(temp_len<2)continue;
			case '/':
				if(t_s=='t' && temp_len<2)
				{
					t_s='c';
					continue;
				}
			default:
				position.col++;
				if(temp_len==1 && t_s=='t')t_s='o';
				temp_len++;
				temp_word=(char *)realloc(temp_word,sizeof(char)*(temp_len));
				temp_word[temp_len-2]=s;
				temp_word[temp_len-1]='\0';
		}
	}
	show();
	map();
}
void c_package::map()
{
	u32 cnt = 0;
	item * tmp=tag_list.head;
	while(tmp!=NULL)
	{
		cnt++;
		uchar type=tmp->flag;
		if(type=='o')
		{
			que.push(tmp);
			printf("\nque < %s (c %d)%d",tmp->loc,que.len,tmp->position.line);fflush(stdout);
		}
		else if(type=='c')
		{
			// compare dont use function use method
			if(tmp->chksum.list[0]==que.last->chksum.list[0])
			{
				if(tmp->chksum.head_end==que.last->chksum.head_end)
				{
					que.pop();
				}
			}
		}
		tmp=tmp->out;

	}
	
	printf("\nremaining %d %d",que.len,cnt);

	for(int i=0;i<que.len;i++)
	{
		printf("\nidx:%d flg:%c chk:%u line:%u %s",que.list[i]->index,que.list[i]->flag,que.list[i]->chksum.list[0],que.list[i]->position.line,que.list[i]->loc);
	}
}
void c_package::search(char * str)
{
	tag_list.search(str);
}
bool c_package::compare(uint idx1,uint idx2)
{
	return tag_list.compare(idx1,idx2);
}
void c_package::show()
{
	tag_list.show();
}
void que_c::push(item* ptr)
{
	len++;
	list=(item **)realloc(list,len*sizeof(item*));
	list[len-1]=ptr;
	last=list[len-1];
	Q_LOG_PUSH();
}
void que_c::pop()
{
	Q_LOG_ITM_DEST();
	list[len-1]=NULL;
	len--;
	list=(item **)realloc(list,len*sizeof(item*));
	if(len>0)last=list[len-1];
}
que_c::que_c()
{
	list=(item **) malloc(sizeof(item *));
	len=0;
}
que_c::~que_c()
{
	free(list);
}
void que_c::show()
{
	for(u32 i=0;i<len;i++)
	{
		printf("%u %s\n",i,list[i]->loc);
	}
}