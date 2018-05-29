#include <stdio.h>
#include <stdlib.h>
#include "LinkedList_ptr_L.h"


void Error_Exit(char *s);
void Find_a_Path(char **G, int N, int start, ptr_L **path, ptr_L **path_end);
void Print_Path(ptr_L *path);

ptr_L *Find_Euler(char **G, int N, int start) {
	ptr_L *path = NULL, *path_end = NULL;

	ptr_L *p;	// for scan	
	ptr_L *new_path,*new_path_end;
	int j;

	Find_a_Path(G,N,start,&path,&path_end);	//Find a path with start.	
	
	for(p = path->p; p->p != NULL; p = p->p){
		for(j=0; j<N; j++){
			if(G[p->i][j] != 0){
				new_path = NULL;	new_path_end = NULL;
				Find_a_Path(G,N,p->i,&new_path,&new_path_end);
				ptr_L *temp = p->p;
				p->p = new_path->p;
				new_path_end->p = temp;	// insertion of new path
				Free_ptr_L(new_path);
			}
		}
	}//scan vertex in path has any edges
	return path;

}

void Find_a_Path(char **G, int N, int start, ptr_L **path, ptr_L **path_end) {

	//start with start vertex, find any path which couldn't progress more over.

	int i = start;
	int j;

	if(*path == NULL && *path_end == NULL){
		ptr_L *startVertex = Alloc_ptr_L();
		startVertex->i = i;
		startVertex->p = NULL;
		*path = startVertex;
		*path_end = startVertex;
	} // initiate path and path_end with start vertex

	for(j=0; j<N; j++){
		if(G[i][j] != 0){
				ptr_L *visitVertex = Alloc_ptr_L();
				visitVertex->i = j;
				visitVertex->p = NULL;
				(*path_end)->p = visitVertex;
				*path_end = visitVertex;
				--G[i][j];	--G[j][i];
				i=j;	j=-1;
		}
	}
	return;
}

int getOddDegreeNum(char **G, int N, int *start) {
	// G : nxn Matrix
	int oddDegree = 0;
	int cntEdge = 0;
	int i,j;
	for(i=0; i<N; i++){
		cntEdge = 0;
		for(j=0; j<N; j++){
			cntEdge += G[i][j];
		}
		if(cntEdge%2 != 0){
			++oddDegree;
			*start = i;	// start vertex will be setted the last investicated vertex which has odd degree. 
		}
	}

	return oddDegree;
}

void Print_Path(ptr_L *path) {
	ptr_L *p;
	for (p = path; p != NULL; p = p->p) {
		printf("%d ",p->i);
	}
	printf("\n");
}