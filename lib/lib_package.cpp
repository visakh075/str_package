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
	read(url);
	//packet_list.show();
}
void c_package::read(char * url){
	FILE *handler = fopen(url,"r+b");
	size_t len_string=0;
	long temp_len=1;
	char s;
	char *temp_word=(char *)malloc(sizeof(char));
	char t_s='t';
	//char t_t='o';
	
	//init_tag_list();

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
					
					packet_list.push(temp_word);
					packet_list.getI(0)->flag=t_s;
					packet_list.getI(0)->path=-1;
					tag_list_count++;
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
	//tag_par_list=(int *)realloc(tag_par_list,tag_list_count*sizeof(int));
	map(0,tag_list_count-1,-1);
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