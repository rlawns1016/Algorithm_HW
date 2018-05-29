#include<stdio.h>
#include<math.h>

int ceiling(double x);
int floor_(double x);
int round_(double x);

int main(void){
	
	
	double x;
	int y;
	
	while(1){
		scanf("%lf",&x);
		if(x == -1)	break;
		y = round_(x);
		printf("\n%d\n",y);
	}


	return 0;
}

int ceiling(double x){
	//올림
	if(x-(int)x == 0 || x < 0)	return (int)x;
	else return (int)x+1;
}
int floor_(double x){
	//내림
	if(x-(int)x == 0 || x > 0) return (int)x;
	else return (int)x-1;
}
int round_(double x){
	if(x-(int)x == 0)	return (int)x;
	if(x>0)	return (int)(x+0.5);
	else	return (int)(x-0.5);
	

}