#include "lib_package.h"
#include <cstdio>
#include <stdlib.h>
#include "lib_strlist.h"
size_t getfs(char *filename){
	FILE *fp;
	fp=fopen(filename,"rb");
	if(fp!=NULL){
		fseek(fp, 0L, SEEK_END); 
		size_t res = ftell(fp);
		fclose(fp);return(res);}
	return(0);}
package::package(char * url)
{
	package_handler=fopen(url,"r+b");
	if(package_handler)
	{
		printf("file size %lu",getfs(url));
	}
	else
	{
		printf("package non exixstant");fflush(stdout);
	}
}
void package::read(char * url){
	FILE *handler = fopen(url,"r+b");
	size_t len_string=0;
	size_t str_len,temp_len=0;
	char s;
	char *temp_word=(char *)malloc(sizeof(char));
	bool t_s=false;
	char t_t='o';
	
	init_tag_list();

	while(!feof(handler))
	{   
		s=fgetc(handler);
		if(s=='<' || s=='>')
		{
			if(s=='<') t_s=true; else t_s=false;
			if(temp_len){
				tag_list_count++;
				add_list(temp_word,temp_len,(t_s)?'v':t_t);
			}
			temp_len=0;t_t='o';
			temp_word=(char *)malloc(sizeof(char));
		}
		else if(s!='\n' && s!='\0')
		{
			if(t_s && s=='/' && temp_len==0){t_t='c';continue;}
			temp_word=(char *)realloc(temp_word,sizeof(char)*(++temp_len));
			temp_word[temp_len-1]=s; 
		}
	}
	tag_par_list=(int *)realloc(tag_par_list,tag_list_count*sizeof(int));
	map(0,tag_list_count-1,-1);}
void package_header::map(int from,int to,int p)
{
	tag_par_list[from]=p;
	for(int f=from+1;f<=to;f++) tag_par_list[f]=from;

	for(int f=from+1;f<to;f++)
	{
		if(tag_flag_list[f]!='o') continue;
		for(int l=f;l<to;l++)
		{
			if(tag_flag_list[l]!='c') continue;
			if(compare_tag(f,l)){map(f,l,from);f=l;break;}
		}
	}
}