#include "lib_package.h"
#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
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

	while(!feof(handler))
	{   
		s=fgetc(handler);
		
		switch(s)
		{
			case '<':
			case '>':
				//t_s=~t_s;
				
				if(temp_len>1)
				{
					
					tag_list.push(temp_word);
					tag_list.getI(0)->flag=t_s;
					tag_list.getI(0)->path=-1;
					tag_list_len++;
					temp_len=1;
					//free(temp_word);
					temp_word=(char *)malloc(sizeof(char));
					temp_word[0]='\0';
					
					//t_='o';
				}
				t_s=(s=='>') ? 'v':'t';
				break;
			
			case '\n':
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
				if(temp_len==1 && t_s=='t')t_s='o';
				temp_len++;
				temp_word=(char *)realloc(temp_word,sizeof(char)*(temp_len));
				temp_word[temp_len-2]=s;
				temp_word[temp_len-1]='\0';
		}
	}
	map(0,tag_list_len-1,-1);
}
void c_package::map(int from,int to,int p)
{
	// tag_par_list[from]=p;
	// for(int f=from+1;f<=to;f++) tag_par_list[f]=from;

	// for(int f=from+1;f<to;f++)
	// {
	// 	if(tag_flag_list[f]!='o') continue;
	// 	for(int l=f;l<to;l++)
	// 	{
	// 		if(tag_flag_list[l]!='c') continue;
	// 		if(compare_tag(f,l)){map(f,l,from);f=l;break;}
	// 	}
	// }
}
void c_package::search(char * str)
{
	tag_list.search(str);
}
int c_package::compare(uint idx1,uint idx2)
{
	tag_list.compare(idx1,idx2);
}
void c_package::show()
{
	tag_list.show();
}