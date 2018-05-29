#include "Graph_adj_array.h"
#include "Graph_adj_array_extern.h"
#include "Graph_adj_array_function.h"

void Read_Graph_adj_array ( ) {
	// read graph information
	int i;
	int vf,vr,Ecost;
	//initiate V
	for(i=0;i<Vnum;i++){
		V[i].f_hd = -1;
		V[i].r_hd = -1;
		V[i].name = i;
	}
	//initiate E
	for(i=0;i<Enum;i++){
		E[i].fp = -1;
		E[i].rp = -1;
		E[i].name = i;
	}
	//read edges info
	for(i=0; i<Enum; i++){
		scanf_s("%d %d %d", &vf, &vr, &Ecost);
		E[i].vf = vf;
		E[i].vr = vr;
		E[i].cost = Ecost;		
		//vertex : f_hd / r_hd가 NONE(-1)이면 edge index write, NONE이 아니면 E에 저장후에  f_hd / r_hd에 edge index write 
		if(V[vf].f_hd != -1)
			E[i].fp = V[vf].f_hd;
		V[vf].f_hd = i;

		if(V[vr].r_hd != -1)
			E[i].rp = V[vr].r_hd;
		V[vr].r_hd = i;
	}
}



void DFS_Tree_adj_array ( int src ) {  // src = source node index
	
	V[src].flag = true;
	int i;
	i = V[src].f_hd;	// i = edge index, for front header(list)
	for(; i !=-1; i=E[i].fp){
		if(E[i].flag == false && (V[E[i].vf].flag == false || V[E[i].vr].flag == false)){	// if not visited
			E[i].flag = true;
			Tree_cost+=E[i].cost;
			if(V[E[i].vf].flag == false)	DFS_Tree_adj_array(E[i].vf);	//do DFS recursively
			else	DFS_Tree_adj_array(E[i].vr);	
		}		
	}
	i = V[src].r_hd;	//i = edge index, for rear header(list)
	for(; i !=-1; i=E[i].rp){
		if(E[i].flag == false && (V[E[i].vf].flag == false || V[E[i].vr].flag == false)){	// if not visited
			E[i].flag = true;
			Tree_cost+=E[i].cost;
			if(V[E[i].vf].flag == false)	DFS_Tree_adj_array(E[i].vf);	//do DFS recursively
			else	DFS_Tree_adj_array(E[i].vr);	
		}		
	}
}
