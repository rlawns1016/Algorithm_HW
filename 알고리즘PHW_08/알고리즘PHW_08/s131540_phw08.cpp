#include<stdio.h>
#include<math.h>
#define SIZE 9	//SIZE*SIZE SUDOKU

bool promising(int x, int y, int v);
bool sudoku();
unsigned int arr[SIZE][SIZE];
int main(){	
	//INPUT
	for(int i=0; i<SIZE; i++)
		for(int j=0; j<SIZE; j++){
			scanf("%d",&arr[i][j]);
			if(arr[i][j] < 0 || arr[i][j] > SIZE){
				printf("Wrong Input");
				return -1;
			}
		}
	//SOLVING PROBLEM
	sudoku();
	//OUTPUT
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
bool promising(int x, int y, int v){
	//v가 arr[x][y]에 있어도 되는지, 즉 promising한지 check한다.
	int m_size = sqrt((float)SIZE);
	//x행과 y열에 v가 있는지 check한다.
	for(int i=0; i<SIZE; i++)
		if(arr[x][i] == v || arr[i][y] == v)
			return false;
	//(x,y)를 포함한 3*3 box에 v가 있는지 check한다.
	for(int i = (x/m_size)*m_size; i < (x/m_size)*m_size+m_size; i++)
		for(int j= (y/m_size)*m_size; j < (y/m_size)*m_size+m_size; j++)
			if(arr[i][j] == v)
				return false;	
	return true;	
}
bool sudoku(){
	//reculsive하게 해결한다.
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(arr[i][j] == 0){
				int k;
				for(k=1; k<=SIZE; k++){
					if(promising(i,j,k)){
						//k 가 (i,j)에서 promising하면 k를 입력하고 이함수를 다시 호출한다.
						arr[i][j] = k;
						if(sudoku())
							break;
					}
				}
				//k가 promising하지 않다면 상위단계의 arr[i][j]값이 k++로 바뀐다.
				if( k > SIZE){
					arr[i][j] = 0;
					return false;
				}
			}
		}
	}
	return true;
}