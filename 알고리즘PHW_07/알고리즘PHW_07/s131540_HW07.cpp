#include "Graph_include.h"


// any function definitions here
void SWAP(int *a, int *b);
void Push_Heap(int *P1, int *P2, int *P3,int index, int v);
int Pop_Heap(int *P1, int *P2, int *P3, int index);
void Adjust_Heap(int *P1, int *P2, int *P3,int index, int v);
void Find_Max(int *P1, int *m1, int *m3, int Vnum);
// You must not declare any global variable

int SPT_Dijkstra(		// return SPT cost
	int src,			// source vertex index
	int Vnum, vertex *V, int Enum, edge *E,		// Graph data(the same as in HW04, 05)
	int *P1, int *P2, int *P3, int *P4,			// scratch int  storage of size (Vnum+1)
	bool *P5,									// scratch bool storage of size (Vnum+1)
	int *Maxd1,		// The largest distance (output)
	int *Maxd3      // The third largest distance (output)
) {
	//P1 -> distance[]
	//P2 -> heap[]
	//P3 -> heap_idx[]
	//P4 -> previous edge
	//P5 -> found[]
	int cost=0;
	int heap_index = 0;
	for(int i=0; i<Vnum; i++){
		P5[i] = false;
		P1[i] = INT_MAX;
		P2[i] = -1;
		P3[i] = -1;
		P4[i] = -1;
	}
	P5[src] = true;
	P1[src] = 0;
	P4[src] = -1;
	int v;
	//src에 인접한 vertex들의 distance[] 조사
	for(int i= V[src].f_hd; i != -1; i = E[i].fp){
		//i는 간선번호
		if(E[i].vf == src)	v = E[i].vr;
		else	v = E[i].vf;
		P4[v] = i;
		E[i].flag = true;
		cost+=E[i].cost;
		P1[v] = E[i].cost;
	}
	v = src;
	for(int i = V[src].r_hd; i!= -1; i = E[i].rp){
		if(E[i].vf == src)	v = E[i].vr;
		else	v = E[i].vf;
		P4[v] = i;
		E[i].flag = true;
		cost+=E[i].cost;
		P1[v] = E[i].cost;
	}
	//{V}-src Heap 구성
	for(int i=0; i<Vnum; i++){
		if(i == src)	continue;
		Push_Heap(P1,P2,P3,heap_index++,i);
	}
	///////////////End of Initialization//////////////////

	int w;
	//Min heap 에서 POP하면서 distance[] 구하기
	while(P2[0] != -1){
		v = Pop_Heap(P1,P2,P3,heap_index--);
		P5[v] = true;
		for(int i= V[v].f_hd; i != -1; i = E[i].fp){
			if(E[i].vf == v)	w = E[i].vr;
			else	w = E[i].vf;
			if(P5[w] == false && P1[v] + E[i].cost	< P1[w]){
				P1[w] = P1[v] + E[i].cost;
				Adjust_Heap(P1,P2,P3,heap_index,w);
				//전에 사용했던 edge를 false로 set하고 cost를 빼준다.
				if(P4[w] != -1){
				E[P4[w]].flag = false;
				cost -= E[P4[w]].cost;
				}
				//이번에 사용한 edge를 true로 set하고 cost를 더해준다.
				P4[w] = i;
				E[i].flag = true;
				cost+=E[i].cost;
			}
		}
		for(int i= V[v].r_hd; i != -1; i = E[i].rp){
			if(E[i].vf == v)	w = E[i].vr;
			else	w = E[i].vf;
			if(P5[w] == false && P1[v] + E[i].cost	< P1[w]){
				P1[w] = P1[v] + E[i].cost;
				Adjust_Heap(P1,P2,P3,heap_index,w);
				//전에 사용했던 edge를 false로 set하고 cost를 빼준다.
				if(P4[w] != -1){
				E[P4[w]].flag = false;
				cost -= E[P4[w]].cost;
				}
				//이번에 사용한 edge를 true로 set하고 cost를 더해준다.
				P4[w] = i;
				E[i].flag = true;
				cost+=E[i].cost;
			}
		}
	}
	//distance[]에서 첫번째와 세번째로 큰 값을 찾는다.
	Find_Max(P1,Maxd1,Maxd3,Vnum);
	return cost;
}

void Read_Graph(int Vnum, vertex *V, int Enum, edge *E) { 
	// construct the adjacency list of a graph using array style linked list
	int i;
	int vf,vr,Ecost;
	//initiate V
	for(i=0;i<Vnum;i++){
		V[i].f_hd = -1;
		V[i].r_hd = -1;
	}
	//initiate E
	for(i=0;i<Enum;i++){
		E[i].fp = -1;
		E[i].rp = -1;
		E[i].flag = false;
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
void SWAP(int *a, int *b){
	//swap하는 함수이다.
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void Push_Heap(int *P1, int *P2, int *P3, int index, int v){
	//Vertex v를 heap에 push하는 함수이다.
	P2[index] = v;
	P3[v] = index;
	while(index > 0 && P1[P2[index]] < P1[P2[(index-1)/2]]){
		SWAP(&P2[index],&P2[(index-1)/2]);
		SWAP(&P3[P2[index]],&P3[P2[(index-1)/2]]);
		index = (index-1)/2;
	}
}
int Pop_Heap(int *P1, int *P2, int *P3, int index){
	//min heap에서 root를 pop시키고 heap을 재구성하는 함수이다.
	int pop = P2[0];
	int i=0;
	P3[P2[0]] = -1;
	P2[0] = P2[--index];
	P2[index] = -1;
	if(P2[0] != -1)
		P3[P2[0]] = 0;
	while((i*2+2)<=index){
		if(P1[P2[i]] > P1[P2[(i*2)+1]] && P2[(i*2)+1] >= 0){			
			if(P1[P2[(i*2)+1]] > P1[P2[(i*2)+2]] && P2[(i*2)+2] >= 0){
				//두 자식중 작은 값과 swap한다.
				SWAP(&P2[i],&P2[(i*2)+2]);
				SWAP(&P3[P2[i]],&P3[P2[(i*2)+2]]);
				i = i*2+2;
				continue;
			}			
			SWAP(&P2[i],&P2[(i*2)+1]);
			SWAP(&P3[P2[i]],&P3[P2[(i*2)+1]]);
			i = i*2+1;
			continue;
		}
		else if(P1[P2[i]] > P1[P2[(i*2)+2]] && P2[(i*2)+2] >= 0){
			SWAP(&P2[i],&P2[(i*2)+2]);
			SWAP(&P3[P2[i]],&P3[P2[(i*2)+2]]);
			i = i*2+2;
			continue;
		}
		break;
	}
	return pop;
}
void Adjust_Heap(int *P1, int *P2, int *P3,int index, int v){	
	//distance[v]가 작아졌을때 min heap을 재구성하는 함수이다.
	int i = P3[v];
	// i는 P2[]에서 v의 index번호
	// distance[v]가 작아졌을때만 이 함수가 호출되므로 위로만 비교한다.
	while(i > 0 && P1[P2[i]] < P1[P2[(i-1)/2]]){
		SWAP(&P2[i],&P2[(i-1)/2]);
		SWAP(&P3[P2[i]],&P3[P2[(i-1)/2]]);
		i = (i-1)/2;
	}
}
void Find_Max(int *P1, int *m1, int *m3, int Vnum){
	//distance[]에서 첫번째와 세번째로 큰 값을 찾는다.
	//단순하게 O(3*Vnum) = O(Vnum)의 시간복잡도로 구현했다.
	int t1=0,t2=0,t3=0;
	int i1,i2;
	for(int i=0; i<Vnum; i++)
		if(t1 < P1[i]){
			t1  = P1[i];
			i1 = i;
		}
	*m1 = t1;
	for(int i=0; i<Vnum; i++)
		if(t2 < P1[i] && i != i1){
			t2 = P1[i];
			i2 = i;
		}
	for(int i=0; i<Vnum; i++)
		if(t3 < P1[i] && i != i1 && i != i2)	t3 = P1[i];
	*m3 = t3;
}
// You may write any functions here (eg. heap insert, delete, adjustment)

