#include<stdio.h>
#include<stdlib.h>

int findcandidate(int *arr,int start, int end){

	/*
		n is odd -> �ΰ��� ¦���� ������ majority element���� check ; ������ return �ƴϸ� discard
			
	*/
	
	int x = find(arr,start,(start+end-1)/2);
	int y = find(arr,(start+end-1)/2+1,end);
	

}

int main(void){
	int n;
	scanf("%d",&n);
	int *arr = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	int a = find(arr,0,n);
	if(a == -1)	puts("MN not Exists\n");
	else	printf("Answer : %d\n", a);
	
	system("PAUSE");
	return 0;
}