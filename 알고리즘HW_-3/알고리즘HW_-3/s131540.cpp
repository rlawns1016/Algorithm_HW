#include<stdio.h>
#include<stdlib.h>

typedef struct dbl_list{
	int i;	// may have more data fields
	struct dbl_list *lp, *rp;	//lp : backward	//rp : foward
}dbl_L;
dbl_L *dbl_L_pool = NULL;
int dbl_L_cnt = 0;
int Total_Used_Memory = 0;

void Error_Exit(char *s){
	printf("%s\n",s);
	exit(-1);
}
dbl_L *Alloc_dbl_L(void){
	dbl_L *p;
	if(dbl_L_pool == NULL){
		p = (dbl_L*)malloc(sizeof(dbl_L));
		if(p == NULL){
			Error_Exit("Error in Alloc_dbl_L");
		}
		Total_Used_Memory += sizeof(dbl_L);
	}
	//*****************my code*******************//
	else{
		p = dbl_L_pool;
		dbl_L_pool = p->rp;
	}
	p->rp = NULL;
	p->lp = NULL;
	++dbl_L_cnt;
	return(p);
	//*******************************************//
}
void Free_dbl_L(dbl_L* p){
	p->rp = dbl_L_pool;
	dbl_L_pool = p;
	--dbl_L_cnt;
}
void Free_dbl_L_pool(void){
	//call only once when exit
	dbl_L *p;
	//*****************my code*******************//
	p = dbl_L_pool;
	while(p != NULL){
		dbl_L_pool = p->rp;
		free(p);
		Total_Used_Memory -= sizeof(dbl_L);
		p = dbl_L_pool;
	}
	//*******************************************//
	if(dbl_L_cnt != 0)
		Error_Exit("dbl_L_cnt must be 0");
	dbl_L_pool = NULL;
}
void Insert_dbl_L(dbl_L **Q, dbl_L *p){
	//insert p to the front of the dbl.
	//*Q is the header ptr of the dbl.
	if(*Q == NULL){
		p->lp = p->rp = NULL;
	}
	//*****************my code*******************//
	if(*Q == NULL){
		*Q = p;
	}
	else{
		p->rp = *Q;
		p->lp = NULL;
		(*Q)->lp = p;
		*Q = p;
	}
	//*******************************************//
}
void Delete_dbl_L(dbl_L **Q, dbl_L *p){
	//delete p from the dbl *Q
	if(*Q == p){
		*Q = p->rp;
		if(*Q != NULL)
			(*Q)->lp = NULL;
	}
	//*****************my code*******************//
	else{
		p->lp->rp = p->rp;
		if(p->rp != NULL)
			(p->rp)->lp = p->lp;
	}
	Free_dbl_L(p);
	//*******************************************//
}
void main(void){
	dbl_L *Q = NULL;
	dbl_L *p;
	for(int i=1; i<=9; i++){
		p = Alloc_dbl_L();
		p->i = i;
		Insert_dbl_L(&Q,p);
	}
	//search 7 in the list and delete it
	for(p=Q; p!=NULL; p=p->rp){
		if(p->i == 7){
			Delete_dbl_L(&Q,p);
			break;
		}
	}
	//remove the first elment
	Delete_dbl_L(&Q,Q);
	//remove the last element
	for(p=Q; p!=NULL; p=p->rp){
		if(p->rp == NULL){
			Delete_dbl_L(&Q,p);
			break;
		}
	}
	//forward printing the list
	printf("**Forward checking\n");
	for(p=Q; p!=NULL; p=p->rp){
		//must be "8 6 5 4 3 2"
		printf("%d ",p->i);
	}
	printf("\n");
	//reverse printing the list
	for(p=Q; p!=NULL; p=p->rp){
		if(p->rp == NULL){
			break;
		}
	}
	printf("**Backward checking\n");
	for(; p!=NULL; p=p->lp){
		//must be "2 3 4 5 6 8"
		printf("%d ",p->i);
	}
	//Free the dbl list Q
	while(Q!=NULL){
		Delete_dbl_L(&Q,Q);
	}
	//Deallocate the storage pool
	Free_dbl_L_pool();
	//check if management error
	if(Total_Used_Memory != 0){
		Error_Exit("MM Error(dbl)");
	}
	getchar();
}
