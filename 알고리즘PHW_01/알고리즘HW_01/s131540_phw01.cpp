#include "Graph_adj_list.h"
#include "Graph_adj_list_extern.h"
#include "Graph_adj_list_function.h"

void Read_Graph_adj_list(int Vnum, vertex *V, int Enum, edge *E) {
	// Read graph information and form an adjacent list
	//Vnum : vertex number	Enum : edge number	V : array of vertex	E : array of edge
	int i,m,n,c;
	//initiate V with name = i
	for(i=0; i<Vnum; i++){
		V[i].p = NULL;
		V[i].name = i;
	}
	//initiate E and input edge imformation in each vertex.
	for(i=0; i<Enum; i++){		
		scanf_s("%d %d %d", &m, &n, &c);
		E[i].name = i;
		E[i].vf = m;
		E[i].vr = n;
		E[i].cost = c;
		pushQ_ptr_L(&V[m].p,i); 		
		pushQ_ptr_L(&V[n].p,i);				
	}
}

void Free_Graph_adj_list(int Vnum, vertex *V, int Enum, edge *E) {
	// remove the links (ptr_Ls) for the adjacent list
	int i;
	int temp;	//for pop 
	for(i=0; i<Vnum; i++)
		while(V[i].p != NULL)	temp = popQ_ptr_L(&V[i].p);	
}

void DFS_Tree_adj_list (
	int     src,   // source node index
	int     Vnum,  // number of vertices
	vertex *V,     // vertex structure array (starting index 0)
	int     Enum,  // number of edges
	edge   *E,     // edge structure array (starting index 0)
	int    *cost   // accumulated tree cost
) {
	// preform DFS and set the flags of edges in the DFS tree

	// return the DFS tree cost.
	
	// Recursively do DFS.
	V[src].flag = true;
	ptr_L *temp;
	temp = V[src].p;
	while(1){
		//investigate vertex and edges for move on
		while(temp->p != NULL){
			if((E[temp->i].flag == false && V[E[temp->i].vf].flag == false) || (E[temp->i].flag == false && V[E[temp->i].vr].flag == false))
				break;		
			temp = temp->p;
		}
		//end the function if it cannot move anymore.
		if(E[temp->i].flag == true || (V[E[temp->i].vr].flag == true && V[E[temp->i].vf].flag == true))	{return;}
		//change the flag of the edge which is used.
		if(E[temp->i].flag == false){
			E[temp->i].flag = true;
			(*cost)++;
		}
		//recursively do DFS with new vertex where we arrived.
		if(E[temp->i].vr == src)	DFS_Tree_adj_list(E[temp->i].vf,Vnum,V,Enum,E,cost);
		else	DFS_Tree_adj_list(E[temp->i].vr,Vnum,V,Enum,E,cost);
	}
}