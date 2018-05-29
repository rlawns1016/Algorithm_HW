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
	//v�� arr[x][y]�� �־ �Ǵ���, �� promising���� check�Ѵ�.
	int m_size = sqrt((float)SIZE);
	//x��� y���� v�� �ִ��� check�Ѵ�.
	for(int i=0; i<SIZE; i++)
		if(arr[x][i] == v || arr[i][y] == v)
			return false;
	//(x,y)�� ������ 3*3 box�� v�� �ִ��� check�Ѵ�.
	for(int i = (x/m_size)*m_size; i < (x/m_size)*m_size+m_size; i++)
		for(int j= (y/m_size)*m_size; j < (y/m_size)*m_size+m_size; j++)
			if(arr[i][j] == v)
				return false;	
	return true;	
}
bool sudoku(){
	//reculsive�ϰ� �ذ��Ѵ�.
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(arr[i][j] == 0){
				int k;
				for(k=1; k<=SIZE; k++){
					if(promising(i,j,k)){
						//k �� (i,j)���� promising�ϸ� k�� �Է��ϰ� ���Լ��� �ٽ� ȣ���Ѵ�.
						arr[i][j] = k;
						if(sudoku())
							break;
					}
				}
				//k�� promising���� �ʴٸ� �����ܰ��� arr[i][j]���� k++�� �ٲ��.
				if( k > SIZE){
					arr[i][j] = 0;
					return false;
				}
			}
		}
	}
	return true;
}