#include<stdio.h>
#include<vector>
#define MAXIMUM(a,b) a>b ? a:b
using namespace std;

typedef struct Vertex_Info{
	int D0;
	int D1;
	int cost;
}vertex;

int main(){	
	vector<vertex> V;
	vector< vector<int> > E;
	int N;
	//input N
	scanf("%d", &N);
	if(N > 10000 || N < 1){
		printf("WRONG INPUT SIZE!");
		return -1;
	}

	//input vertex 	
	vertex t;
	t.cost =0;
	t.D0 = 0;
	t.D1 = 0;
	V.assign(N+1,t);		
	for(int i=1; i<=N; i++){
		scanf("%d",&V[i].cost);
		V[i].D1 = V[i].cost;	//각 vertex의 D1을 자신의 cost로 초기화한다.
		if(N > 10000){
			printf("WRONG INPUT COST!");
			return -1;
		}
	}
	if(N == 1){
		printf("%d",V[1].cost);
		return 0;
	}
	//input edges
	//vertex m과 n이 인접해있으면 E[m]에 n을 추가하고 마찬가지로 E[n]에 m을 추가한다.
	vector<int> temp;
	E.assign(N+1,temp);
	for(int i=1; i<N; i++){
		int m,n;
		scanf("%d %d", &m, &n);
		E[m].push_back(n);
		E[n].push_back(m);
	}

	//set root
	//인접한 vertex가 1개인 vertex들 중에서 아무거나 root로 지정한다.(-1을 추가하여 .size()를 2로 만든다)
	int root;
	for(int i=1; i<=N; i++)
		if(E[i].size()== 1){
			E[i].push_back(-1);
			root = i;
			break;
		}
	//E[root]에 있는 -1이 아닌 원소가 erase되면 loop를 종료한다.
	while(E[root].size() != 1){
		//leap node들을 temp에 담아놓는다.
		for(int i=1; i<=N; i++){
  			if(E[i].size() == 1){
				temp.push_back(i);
			}
		}
		//leap node들을 E에서 지워가면서 D0와 D1를 계산하면서 올라간다.
		for(int i=0; i<temp.size(); i++){
			V[E[temp[i]][0]].D0 += MAXIMUM(V[temp[i]].D1,V[temp[i]].D0);
			V[E[temp[i]][0]].D1 += V[temp[i]].D0;
			for(vector<int>::iterator it = E[E[temp[i]][0]].begin(); it!=E[E[temp[i]][0]].end(); it++){
				if(*it == temp[i]){
					it = E[E[temp[i]][0]].erase(it);
					E[temp[i]].clear();
					break;
				}
			}
		}
		temp.clear();
	}
	//root의 D0와 D1중 큰 값을 출력한다.
	printf("%d", MAXIMUM(V[root].D0,V[root].D1));
	return 0;
}

