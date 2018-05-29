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
		V[i].D1 = V[i].cost;	//�� vertex�� D1�� �ڽ��� cost�� �ʱ�ȭ�Ѵ�.
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
	//vertex m�� n�� ������������ E[m]�� n�� �߰��ϰ� ���������� E[n]�� m�� �߰��Ѵ�.
	vector<int> temp;
	E.assign(N+1,temp);
	for(int i=1; i<N; i++){
		int m,n;
		scanf("%d %d", &m, &n);
		E[m].push_back(n);
		E[n].push_back(m);
	}

	//set root
	//������ vertex�� 1���� vertex�� �߿��� �ƹ��ų� root�� �����Ѵ�.(-1�� �߰��Ͽ� .size()�� 2�� �����)
	int root;
	for(int i=1; i<=N; i++)
		if(E[i].size()== 1){
			E[i].push_back(-1);
			root = i;
			break;
		}
	//E[root]�� �ִ� -1�� �ƴ� ���Ұ� erase�Ǹ� loop�� �����Ѵ�.
	while(E[root].size() != 1){
		//leap node���� temp�� ��Ƴ��´�.
		for(int i=1; i<=N; i++){
  			if(E[i].size() == 1){
				temp.push_back(i);
			}
		}
		//leap node���� E���� �������鼭 D0�� D1�� ����ϸ鼭 �ö󰣴�.
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
	//root�� D0�� D1�� ū ���� ����Ѵ�.
	printf("%d", MAXIMUM(V[root].D0,V[root].D1));
	return 0;
}

