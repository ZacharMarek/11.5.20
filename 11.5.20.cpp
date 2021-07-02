#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NULL 0
#define CTWL_OK 1
#define CTWL_FAIL 0

typedef struct TWN{
	float data;
	struct TWN *prev;  //ukazovatel na n-1 uzol
	struct TWN *next;  //ukazovatel na n+1 ulol
}TWN;


typedef struct{
	TWN *cur;     //teda ukazovatel kde v zozname som
}CTWL;

void ctwl_cur_step_right(CTWL *list) //ničoho sa nechytam iba posuniem cur
{
	list->cur=list->cur->next;
}

void ctwl_cur_step_left(CTWL *list)
{
	list->cur=list->cur->prev;
}
// https://www.geeksforgeeks.org/doubly-circular-linked-list-set-1-introduction-and-insertion/
//velka pomoc na funkcie insert
TWN *ctwl_insert_left(CTWL* list, float val)
{
	TWN *cur, *novy, *cur_minus;
	
	novy = (TWN*)malloc(sizeof(TWN));
	
	if(novy==NULL)
		return NULL;
	
	novy->data=val;
	
	if(list->cur==NULL)
	{
		list->cur=novy;
		list->cur->next=novy;
		list->cur->prev=novy;	
	}
	else
	{
		cur=list->cur;
		cur_minus=list->cur->prev;
		
		novy->next=cur;
		novy->prev=cur_minus;
		cur_minus->next=novy;
		cur->prev=novy;
		
		ctwl_cur_step_left(list);
	}
	
	return novy;
}

TWN *ctwl_insert_right(CTWL* list, float val)
{
	TWN *cur, *novy, *cur_plus;
	
	novy = (TWN*)malloc(sizeof(TWN));
	
	if(novy==NULL)
		return NULL;
	
	novy->data=val;
	
	if(list->cur==NULL)
	{
		list->cur=novy;
		list->cur->next=novy;
		list->cur->prev=novy;	
		
		return novy;
	}
	else
	{
		cur=list->cur;
		cur_plus=list->cur->next;
		
		novy->prev=cur;			//posledne dve hodiny ped odvzanim som hladal chybu ktora bola v riadku 88 a 89
		novy->next=cur_plus;	//kde som vymenil prev a next čiže sa mi kurzor neposuval a v doleskedku mi vypisovalo
		list->cur->next=novy;	//stale iba prve dva prvky...
		cur_plus->prev=novy;
		
		ctwl_cur_step_right(list);
		
		return novy;
	}
	
}

CTWL *ctwl_create_empty(void)
{
	CTWL *n;
	
	n=(CTWL*)malloc(sizeof(CTWL));
	
	if(n==NULL)
		return NULL;
		
	n->cur=NULL;
	
	return n;	
}

CTWL *ctwl_create_random(unsigned int size) 
{
	CTWL *n;
	float data;
	int i;
	n = ctwl_create_empty();
	
	for(i=0;i<size;i++)
	{
		data=rand()%10;
		n->cur=ctwl_insert_right(n, data);
	}

	return n;
		
		
}

char ctwl_delete(CTWL* list) //odstranenie kurzora
{
	TWN *cur;
	
	if(list->cur==NULL)
		return CTWL_FAIL;
		
	free(cur);	
		
}

void ctwl_print(CTWL *list)
{
	TWN *prvok;
	prvok=list->cur;
	
	printf("%.f ",list->cur->data);
	ctwl_cur_step_right(list);
	
	while(list->cur != prvok)		//kym neprejdeme koliečko
	{
        printf("%.f ", list->cur->data);
        ctwl_cur_step_right(list);
     }
     
	
}


float ctwl_sun_values(CTWL *list)
{
	TWN *prvok;
	float value ;
	
	prvok = list->cur;
	value = list->cur->data;
	
	while(list->cur > prvok)
	{
		value+=list->cur->data; 		//asi som niečo prehliadol
		//list->cur=list->cur->next;
		ctwl_cur_step_left(list);
	}
	
	return value;
}

void ctwl_destroy(CTWL* list)
{

}

main()
{
 int velkost = 5;
 CTWL *zoznam;
 srand(time(0));
 
 zoznam = ctwl_create_random(velkost);
 ctwl_print(zoznam);
 ctwl_sun_values(zoznam);
 
 printf("value : %.f",ctwl_sun_values(zoznam));
}

