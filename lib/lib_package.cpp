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
	printf("comp : %u",cmp);
	show();
}
void c_package::map(int from,int to,int p)
{
	
	for(int f=from;f<=to;f++) tag_list[f]->path=p;
	// fring case the closing tag also
	for(int f=from;f<=to;f++)
	{
		// neglect all tags that are not open
		if(tag_list[f]->flag=='o')
		{
			//  selected open tag

			for(int l=f+1;l<=to;l++)
			{
				// select only closing tags
				if(tag_list[l]->flag=='c')
				{
					cmp++;
					// slected a closing tag
					if(compare(f,l))
					{
						// printf("\n(%d,%d,%s,%s)",f,l,tag_list[f]->loc,tag_list[l]->loc);fflush(stdout);
					
						map(f+1,l-1,f);
						// maping or closing tag
						tag_list[l]->path=f;
						f=l;
						break; // break out from loop of l
					}
				}
			}
		}
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