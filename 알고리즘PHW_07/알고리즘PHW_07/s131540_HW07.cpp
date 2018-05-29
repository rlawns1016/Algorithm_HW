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
	//src�� ������ vertex���� distance[] ����
	for(int i= V[src].f_hd; i != -1; i = E[i].fp){
		//i�� ������ȣ
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
	//{V}-src Heap ����
	for(int i=0; i<Vnum; i++){
		if(i == src)	continue;
		Push_Heap(P1,P2,P3,heap_index++,i);
	}
	///////////////End of Initialization//////////////////

	int w;
	//Min heap ���� POP�ϸ鼭 distance[] ���ϱ�
	while(P2[0] != -1){
		v = Pop_Heap(P1,P2,P3,heap_index--);
		P5[v] = true;
		for(int i= V[v].f_hd; i != -1; i = E[i].fp){
			if(E[i].vf == v)	w = E[i].vr;
			else	w = E[i].vf;
			if(P5[w] == false && P1[v] + E[i].cost	< P1[w]){
				P1[w] = P1[v] + E[i].cost;
				Adjust_Heap(P1,P2,P3,heap_index,w);
				//���� ����ߴ� edge�� false�� set�ϰ� cost�� ���ش�.
				if(P4[w] != -1){
				E[P4[w]].flag = false;
				cost -= E[P4[w]].cost;
				}
				//�̹��� ����� edge�� true�� set�ϰ� cost�� �����ش�.
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
				//���� ����ߴ� edge�� false�� set�ϰ� cost�� ���ش�.
				if(P4[w] != -1){
				E[P4[w]].flag = false;
				cost -= E[P4[w]].cost;
				}
				//�̹��� ����� edge�� true�� set�ϰ� cost�� �����ش�.
				P4[w] = i;
				E[i].flag = true;
				cost+=E[i].cost;
			}
		}
	}
	//distance[]���� ù��°�� ����°�� ū ���� ã�´�.
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
		//vertex : f_hd / r_hd�� NONE(-1)�̸� edge index write, NONE�� �ƴϸ� E�� �����Ŀ�  f_hd / r_hd�� edge index write 
		if(V[vf].f_hd != -1)
			E[i].fp = V[vf].f_hd;
		V[vf].f_hd = i;

		if(V[vr].r_hd != -1)
			E[i].rp = V[vr].r_hd;
		V[vr].r_hd = i;
	}
}
void SWAP(int *a, int *b){
	//swap�ϴ� �Լ��̴�.
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void Push_Heap(int *P1, int *P2, int *P3, int index, int v){
	//Vertex v�� heap�� push�ϴ� �Լ��̴�.
	P2[index] = v;
	P3[v] = index;
	while(index > 0 && P1[P2[index]] < P1[P2[(index-1)/2]]){
		SWAP(&P2[index],&P2[(index-1)/2]);
		SWAP(&P3[P2[index]],&P3[P2[(index-1)/2]]);
		index = (index-1)/2;
	}
}
int Pop_Heap(int *P1, int *P2, int *P3, int index){
	//min heap���� root�� pop��Ű�� heap�� �籸���ϴ� �Լ��̴�.
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
				//�� �ڽ��� ���� ���� swap�Ѵ�.
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
	//distance[v]�� �۾������� min heap�� �籸���ϴ� �Լ��̴�.
	int i = P3[v];
	// i�� P2[]���� v�� index��ȣ
	// distance[v]�� �۾��������� �� �Լ��� ȣ��ǹǷ� ���θ� ���Ѵ�.
	while(i > 0 && P1[P2[i]] < P1[P2[(i-1)/2]]){
		SWAP(&P2[i],&P2[(i-1)/2]);
		SWAP(&P3[P2[i]],&P3[P2[(i-1)/2]]);
		i = (i-1)/2;
	}
}
void Find_Max(int *P1, int *m1, int *m3, int Vnum){
	//distance[]���� ù��°�� ����°�� ū ���� ã�´�.
	//�ܼ��ϰ� O(3*Vnum) = O(Vnum)�� �ð����⵵�� �����ߴ�.
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

