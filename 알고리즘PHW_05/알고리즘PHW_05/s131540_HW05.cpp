#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MINIMUM(a,b)(a<b ? a:b)

void Edit_Distance ( 
	// inputs
	char *SS,		// Source string array
	char *TS,		// Edited string array
	int ins_cost, int del_cost, int sub_cost,	
					// insertion, deletion, substitution cost
	// outputs
	int **Table,    // Cost Table Calculated (2-d array (|SS|+1) x (|TS|+1) will be set)
	char **SR,		// Source string with insertion to T marks '*'
	char **OP,		// Operation sequence('i', 'd', 's', or '.' (nop))
	char **TR,       // Edited string with deletion form S mark '*'
					// NOTE: ST, OP, TR must be allocated inside the function as needed(minimum as possible)
	int  *Mem_Allocated
){
	//initiate Table[i,0] = i. Table[0,j] = j
	int m = strlen(SS);
	int n = strlen(TS);
	for(int i=0; i<=m; i++)	Table[i][0] = i*del_cost;
	for(int j=0; j<=n; j++)	Table[0][j] = j*ins_cost;
	//complete Table
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++){
			Table[i][j] = MINIMUM(Table[i][j-1]+ins_cost,Table[i-1][j]+del_cost);
			if(SS[i-1] == TS[j-1]){
				if(Table[i][j] > Table[i-1][j-1]){	
					Table[i][j] = Table[i-1][j-1];
				}
			}
			else{
				if(Table[i][j] > Table[i-1][j-1]+sub_cost)	{
					Table[i][j] = Table[i-1][j-1]+sub_cost;
				}
			}
		}
	}
	//backtracking
	int len = m+n;
	int i=m, j=n;
	*OP = (char*)malloc((len+1)*sizeof(char));	//일단 *OP를 최대 길이로 Allocate한다.
	*(*OP+len) = '\0';
	int c;
	for(c=len-1; m>=0 && n>=0; c--){
		if((n>0&&(Table[m][n-1]+ins_cost == Table[m][n])) && (m>0&&(Table[m-1][n]+del_cost == Table[m][n]))){
			if(ins_cost <= del_cost){
				//insert
				*(*OP+c) = 'i';
				n--;
			}
			else{
				//delete
				*(*OP+c) = 'd';
				m--;
			}
		}
		else if(n>0&&(Table[m][n-1]+ins_cost == Table[m][n])){
			//insert
			*(*OP+c) = 'i';
			n--;
		}
		else if(m>0&&(Table[m-1][n]+del_cost == Table[m][n])){
			//delete
			*(*OP+c) = 'd';
			m--;
		}
		else if((m>0 && n>0)&&Table[m-1][n-1]+sub_cost == Table[m][n]){
			//substitute
			*(*OP+c) = 's';
			n--;	m--;
		}
		else{	// nop
			if(n==0 && m==0)	break;
			*(*OP+c) = '.';
			n--;	m--;
		}
	}
	c++;
	//substitution발생 횟수는 c와 같다.
	//따라서 c가 0이 아니라면 *OP의 앞쪽에는 쓰래기값이 있을 것이다.
	if(c != 0){
		for(int i=0; i<len-c+1; i++)	*(*OP+i) = *(*OP+i+c);
	}		
	len = strlen(*OP);
	//*OP를 reallocate하고, *SR과 *TR을 *OP와 같은 크기로 allocate한다.
	*OP = (char*)realloc(*OP,(len+1)*sizeof(char));
	*SR = (char*)malloc((len+1)*sizeof(char));
	*TR = (char*)malloc((len+1)*sizeof(char));
	*Mem_Allocated = 3*(len+1);
	*(*SR+len) = '\0';
	*(*TR+len) = '\0';		
	m = i;	n = j;
	i = 0;	j = 0;
	//set *SR & *TR with *OP
	for(int k=0; i<m || j<n; k++){		
		if(*(*OP+k) == 'd'){
			*(*SR+k) = SS[i];
			*(*TR+k) = '*';
			i++;
		}
		else if(*(*OP+k) == 'i'){
			*(*SR+k) = '*';
			*(*TR+k) = TS[j];
			j++;
		}
		else{	// '.' or  's'
			*(*SR+k) = SS[i];
			*(*TR+k) = TS[j];
			i++;	j++;
		}
	}
}