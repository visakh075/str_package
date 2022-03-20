#include "lib_strlist.h"
#include <stdlib.h>
#include <stdio.h>
#include "lib_rtlog.h"
#include <cstddef>

//	DEBUG >>>
	// Definition
	#if(LOG_ENSY==1)
	rtlog map=rtlog(LOG_FILE,NORMAL);
	char buff[LOG_BUFF_SZ];
	#define LOG() map << buff
	#endif
//	DEBUG <<<

// EXTRA >>>
uint strlen(const char * strptr)
{
	uint retVal=0;
	while(*strptr++)retVal++;
	return retVal;
}
uint strlen_s(char * strptr)
{
	uint retVal=0;
	uint maxlen=strlen(strptr);
	while(retVal<maxlen)
	{
		if(strptr[retVal]==' ')break;
		retVal++;
	}
	//while(*strptr++!=' ')retVal++;
	return retVal;
}
void strcpy(const char * frm,char * to)
{
	while((*to++=*frm++)){};
}
s_chksum get_chksum(char * str)
{
	s_chksum retVal;
	retVal.sum=0;
	retVal.len=strlen(str);
	for(uint idx=0;idx<retVal.len;idx++)
	{
		retVal.sum=retVal.sum+str[idx]*0x10;
	}
	return retVal;
}
uint strcmp_head(char * strx,char *stry)
{

	return 0;
}
// EXTRA <<<

// ITEM >>>
item::item_c(const char * _str)
{
	set(_str);
}
item::item_c()
{
	in=(item_c *)malloc(sizeof(item_c));
	if(in==NULL)
	{
		LOG_STR("memmory allocation error");
	}
	out=(item_c *)malloc(sizeof(item_c));
	if(out==NULL)
	{
		LOG_STR("memmory allocation error");
	}

	loc=(char *)malloc(sizeof(char));
	if(loc==NULL)
	{
		LOG_STR("memmory allocation error");
	}
	len=0;

	LOG_ITM_INIT();
}
item::~item_c()
{
	LOG_ITM_DEST();
	free(loc);
	in=nullptr;
	out=nullptr;
	loc=nullptr;
}
void item::set(const char * strptr)
{
	loc=nullptr;
	
	loc=(char *)realloc(loc,sizeof(char)*strlen(strptr)+1);
	
	if(loc!=nullptr)
	{
		strcpy(strptr,loc);
		len=strlen(strptr);
	}
	else
	{
		LOG_STR("memmory re-allocation error");
	}
	crunch();
	LOG_ITM_SET();
}
void item::reset(const char * strptr)
{
	if(loc!=nullptr)
	{
		free(loc);
	}
	set(strptr);
}
void item::probe()
{
	LOG_ITM_PROBE();
	//printf("\np:%p l:%p [i:%p o:%p %3ld %6ld] %s",this,loc,in,out,flag,path,loc);
}
void item::con_tail(item * _tail)
{
	out=_tail;
	_tail->in=this;
}
void item::con_head(item * _head)
{
	in=_head;
	_head->out=this;
}
item * item::push(const char * _str)
{
	item_c* temp;
	temp=(item_c *) malloc(sizeof(item));
	temp->set(_str);
	out=nullptr;
	temp->out=this;
	return temp;

}
void item::crunch()
{
	chksum.list=(uint *)malloc(sizeof(uint));
	chksum.len=0;
	uint tmpChkSum=0;
	char s;
	for(uint idx=0;idx<len;idx++)
	{
		s=loc[idx];

			tmpChkSum=tmpChkSum+0x10*loc[idx];

		if(s==' ' || idx==len-1)
		{
			if(chksum.len==0)chksum.head_end=idx;
			chksum.list=(uint *)realloc(chksum.list,++chksum.len);
			chksum.list[chksum.len-1]=tmpChkSum;
			tmpChkSum=0;
		}
	}
	
}
// ITEM <<<

// STRLIST >>>
strlist::strlist_c()
{
	LOG_STR("strlist init");
	head=(item *)malloc(sizeof(item));
	LOG_STR("memmory allocation head");
	
	tail=(item *)malloc(sizeof(item));
	LOG_STR("memmory allocation tail");
	
	len=0;
	//search_results=(item **)malloc(sizeof(item *));
}
strlist::~strlist_c()
{
	if (len<3)
	{
		//free(head->loc);free(tail->loc);
		tail->~item_c();
		head->~item_c();
		free(tail);
		free(head);
	}
	else
	{
		item * temp =nullptr;
		temp=tail;
		item * x_temp;
		while(temp!=nullptr)
		{
			x_temp=temp->in;
			temp->~item_c();
			free(temp);
			temp=x_temp;
		}

	}
	LOG_STR("strlist deleted");
}
void strlist::probe()
{
	printf("strlist probe\nh:%p t:%p\n",head,tail);
}
void strlist::push(const char * _str)
{
	
	if(len==0)
	{
		head->set(_str);
		head->in=nullptr;
		head->out=nullptr;
		head->index=0;
		len=1;
	}
	else if(len==1)
	{
		tail->set(_str);
		head->con_tail(tail);
		tail->out=nullptr;
		tail->index=1;
		len=2;
	}
	else
	{
		item * temp=nullptr;
		temp=(item*)malloc(sizeof(item));
	
		temp->set(_str);
		tail->con_tail(temp);
		tail=temp;
		tail->index=len;
		len++;
	}
	
}
void strlist::show()
{
	// uint idx=0;
	if(len==0)
	{

	}
	else if(len==1)
	{
		head->probe();
		//idx=1;
	}
	else
	{
		// idx++;
		item * temp=nullptr;
		temp=head;
		while(temp!=nullptr)
		{
			temp->probe();
			temp=temp->out;
		}
	}
}
item * strlist::get(uint idx)
{
	if(idx==0) return head;
	else if(idx>0 && idx<=len)
	{
		uint count=0;
		item * temp;
		temp=head;
		while(count<idx)
		{
			temp=temp->out;
			count++;
		}
		return temp;
	}
	return nullptr;
}
item * strlist::getI(uint idx)
{
	if(idx==0 && len==1)
	{
		return head;
	}
	else if(idx==0) return tail;

	else if(idx>0 && idx<=len)
	{
		uint count=0;
		item * temp;
		temp=tail;
		while(count<idx)
		{
			temp=temp->in;
			count++;
		}
		return temp;
	}
	return nullptr;
}
item * strlist::operator[] (uint index)
{
	return get(index);
}
void item::operator = (const char * strptr)
{
	reset(strptr);
}
void strlist::search(char * srckey)
{
	LOG_STR("\nSearch");
	s_chksum str_chksum=get_chksum(srckey);
	item * tag;
	for(uint i=0;i<len;i++)
	{
		tag=get(i);

		if(tag->chksum.list[0]==str_chksum.sum && (tag->len==str_chksum.len))
		{
			tag->probe();
		}
	}
}
bool strlist::compare(uint x,uint y)
{
	item * strx=get(x);
	item * stry=get(y);

	if(strx->chksum.head_end==stry->chksum.head_end)
	{
		if(strx->chksum.list[0]==stry->chksum.list[0])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
// STRLIST <<<