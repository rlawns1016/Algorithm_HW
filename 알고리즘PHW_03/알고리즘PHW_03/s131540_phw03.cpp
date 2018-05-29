#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 1000001

//using doubly linked list
typedef struct dbl_list{
	char c;	
	struct dbl_list *lp, *rp;	//lp : backward	//rp : foward
}dbl_L;

void Error_Exit(char *s){
	printf("%s\n",s);
	exit(-1);
}

dbl_L *Alloc_dbl_L(void){
	//allocate dbl_L and initiate lp, rp
	dbl_L *p;
	p = (dbl_L*)malloc(sizeof(dbl_L));
	if(p == NULL){
		Error_Exit("Error in Alloc_dbl_L");
	}
	p->rp = NULL;
	p->lp = NULL;
	return(p);
}
 
void Delete_dbl_L(dbl_L** p){
	//if get '-', delete left character of cursor.
	if(*p == NULL || (*p)->lp == NULL)	return;
	else{
		dbl_L *temp = *p;
		(*p)->lp->rp = (*p)->rp;
		if((*p)->rp != NULL)	(*p)->rp->lp = (*p)->lp;
		*p = temp->lp;
		delete(temp);
	}
}

void Move_Right(dbl_L **p){
	//if get '>', move cursor to right character
	if(*p == NULL || (*p)->rp == NULL)	return ;
	else	*p = (*p)->rp;
	return ;
}

void Move_Left(dbl_L **p){
	//if get '<', move cursor to left character
	if(*p == NULL || (*p)->lp == NULL)	return ;
	else	*p = (*p)->lp;
	return ;
}

void Insert_dbl_L(dbl_L** p, char c){
	//if get any other characters, insert to left side of cursor 
	if(*p == NULL){
		*p = Alloc_dbl_L();
		(*p)->c = c;
	}
	else{
		dbl_L* temp;
		temp = Alloc_dbl_L();
		temp->c = c;
		temp->rp = (*p)->rp;
		if((*p)->rp != NULL)	(*p)->rp->lp = temp;
		(*p)->rp = temp;
		temp->lp = *p;
		*p = temp;
	}
}

int main(void){
	int T;	//test case
	scanf("%d",&T);
	getchar();	//ignore '\n'
	dbl_L **Q;
	Q = (dbl_L**)malloc(T*sizeof(dbl_L*));	//store T results in Q
	for(int i=0; i<T; i++){
		dbl_L *cursor = NULL;	//use it as cursor
		char str[MAX_LENGTH];	//for store input string
		Q[i] =Alloc_dbl_L();
		fgets(str,sizeof(str),stdin);	//input string
		for(int j=0; str[j]!='\0'; j++){
			switch(str[j])
			{
			case '<':
				Move_Left(&cursor);
				break;
			case '>':
				Move_Right(&cursor);
				break;
			case '-':
				Delete_dbl_L(&cursor);
				break;
			case '\n':
				break;
			default:
				Insert_dbl_L(&cursor,str[j]);
				if(Q[i]->rp == NULL){
					Q[i]->rp = cursor;	//set Q[i]->rp as header of list
					cursor->lp = Q[i];
				}
			}
		}
	}
	//print and delete Q
	dbl_L *front,*rear;
	for(int i=0; i<T; i++){
		for(front = Q[i]->rp; front->rp != NULL; front = front->rp){
			rear = front->lp;
			printf("%c",front->c);
			delete(rear);	//print front character and delete before character
		}
		printf("%c",front->c);
		delete(front);	//print last character and delete
		printf("\n");
	}
	delete(Q);	
	return 0;
}

