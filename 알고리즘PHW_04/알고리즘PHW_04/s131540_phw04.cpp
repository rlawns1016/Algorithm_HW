#include<stdio.h>
#include<math.h>
#define MINIMUM(a,b) (a<b ? a:b)

unsigned int partition(double *A, unsigned int *P, int p, int r){
	//Quick Sort함수에서 호출하는 함수이다.	
	double x;
	unsigned int i;
	x = A[P[r]];
	i = p-1;
	unsigned int temp;
	for(unsigned int j=p; j<r; ++j){
		if(A[P[j]] <= x){
			temp = P[++i];
			P[i] = P[j];
			P[j] = temp;
		}
	}
	temp = P[i+1];
	P[i+1] = P[r];
	P[r] = temp;
	return i+1;
}

void QuickSort(double *A, unsigned int *P, int p, int r){
	unsigned int q;
	unsigned int THR = 4;
	if(p<r){
		if(r-p+1 > THR){
		q = partition(A,P,p,r);
		QuickSort(A,P,p,q-1);
		QuickSort(A,P,q+1,r);
		}
		//stack overflow를 막기위해서 THR을 설정하여 점의 개수가 THR보다 작은경우  Insertion Sort로 점들을 정렬한다.
		else{
			int temp;
			for(unsigned int i=p; i<=r-1; i++)
				for(unsigned int j=i+1; j<=r; j++)
					if(A[P[i]]>A[P[j]]){
						temp = P[i];
						P[i] = P[j];
						P[j] = temp;
					}
		}
	}
}

void   Sort_by_X_or_Y ( double *A, unsigned int *P, unsigned int N ){
  // input  : A[] (x or y position array of N points)
  //          P[] (index array of X (initital) or Y (during combine))
  //          N   number of points to sort
  // output : P[] (the indices are sorted by x or y position)	
	int THR = 4;
	//점의 개수가 THR보다 큰경우 Quick Sort 알고리즘(O(nlogn))을 사용한다.
	if(N > THR){
		QuickSort(A,P,0,N-1);
	}
	//점의 개수가 THR보다 작은경우 Insertion Sort 알고리즘(O(n^2))을 사용한다.
	else{
		int temp;
		for(unsigned int i=0; i<N-1; i++)
			for(unsigned int j=i+1; j<N; j++)
				if(A[P[i]]>A[P[j]]){
					temp = P[i];
					P[i] = P[j];
					P[j] = temp;
				}
	}
}		

void Merge_by_Y(double *Y, unsigned int L,	unsigned int R, unsigned int *P2, unsigned int *P3){
	//conquer과정에서 Y축으로 정렬하여 merge 하는 함수이다.
	//P2에서 P3로 merge한다.
	unsigned int left = L;
	unsigned int right = (L+R)/2+1;
	unsigned int k=0;

	while(left <= (L+R)/2 && right <= R){
		if(Y[P2[left]] < Y[P2[right]]){
			P3[L+k] = P2[left];
			left++;
		}
		else{
			P3[L+k] = P2[right];
			right++;
		}
		k++;
	}
	if(left > (L+R)/2)
		for(unsigned int i=right; i<=R; i++){
			P3[L+k] = P2[i];
			k++;
		}	
	else
		for(unsigned int i=left; i<=(L+R)/2; i++){
			P3[L+k] = P2[i];
			k++;
		}
}

double Closest_Pair_DC(
	unsigned int L,    unsigned int R,		// left and right indices
	unsigned int *pt1, unsigned int *pt2,   // min dist points indices
    double *X, double *Y,					// input points position array
	unsigned int *P1, unsigned int *P2, unsigned int *P3, // temp index arrays
	unsigned int THR	// threshold value
){
  // Input : L, R, X[], Y[], P1[]
  // Output : pt1, pt2 ( the distance between (X[pt1],Y[pt1]) and
  //                     (X[pt2],Y[pt2]) is the closest )
  //          return the distance value
  // Others ; P2[], P3[] (scratch arrays for D&C algorithm)

	double min = 4294967294;		
	double temp;
	//점의 개수가 THR보다 작으면 brute force로 최소 거리를 찾는다.
	if(R-L+1 <= THR){
		for (unsigned int i=L; i<=R-1; i++){
			for(unsigned int j=i+1; j<=R; j++){
				temp = sqrt(pow(X[P1[j]]-X[P1[i]],2)+pow(Y[P1[j]]-Y[P1[i]],2));
				if(min > temp){
					min = temp;
					*pt1 = P1[i];
					*pt2 = P1[j];
				}
			}
		}
		//P2에 L~R사이의 점들을 Y축으로 정렬하여 저장한다. 
		for(unsigned int i=L; i<=R; i++)	P2[i] = P1[i];
		if(R == L){
			return min;
		}
		else if(R-L == 1){
			if(Y[P2[L]] > Y[P2[R]]){
				int temp;
				temp = P2[L];
				P2[L] = P2[R];
				P2[R] = temp;
			}
		}
		else{
			int temp;
			for(unsigned int i=L; i<=R-1; i++)
				for(unsigned int j=i+1; j<=R; j++)
					if(Y[P2[i]] > Y[P2[j]]){
					temp = P2[i];
					P2[i] = P2[j];
					P2[j] = temp;
					}
		}
		return min;
	}
	//점의 개수가 THR보다 큰 경우 영역을 나눈다.
	double CPl, CPr, CPc, d=min;
	unsigned int tmpPt1, tmpPt2;
	
	CPl = Closest_Pair_DC(L,(L+R)/2,pt1,pt2,X,Y,P1,P2,P3,THR);
	//왼쪽영역의 최소거리에 있는 두점을 기억해둔다.
	tmpPt1 = *pt1;
	tmpPt2 = *pt2;
	CPr = Closest_Pair_DC((L+R)/2+1,R,pt1,pt2,X,Y,P1,P2,P3,THR);
	if(CPr > CPl){	
		*pt1 = tmpPt1;
		*pt2 = tmpPt2;
	}
	//왼쪽영역과 오른쪽영역의 최소거리 중 작은값을 d라고 한다.
	d = MINIMUM(CPl,CPr);
	//이미 sort되어있는 P2를 P3로 merge한다.
	Merge_by_Y(Y,L,R,P2,P3);
	//P2에 P3를 상위단계를 위해 저장해둔다.
	for(unsigned int i=L; i<=R; i++)	P2[i] = P3[i];
	//P2에 있는 점들 중 나눈 경계선에서 |d|이하로 떨어져 있는 점들만 P3에 저장한다.
	int tmp = 0;
	for(unsigned int i=L; i<=R; i++){
		if(((X[P1[(L+R)/2]]-d) < X[P2[i]] && P2[i] <= (L+R)/2) || ((X[P1[(L+R)/2+1]] + d) > X[P2[i]] && P2[i] >= (L+R)/2+1))
			P3[tmp++] = P2[i];
	}
	//CPc를 찾는다.
	tmp--;
	for (unsigned int i=0; i<=tmp-1; i++){
		for(unsigned int j=i+1; j<=tmp; j++){
			if(Y[P3[j]] - Y[P3[i]] >= d)	break;
			temp = sqrt(pow(X[P3[j]]-X[P3[i]],2)+pow(Y[P3[j]]-Y[P3[i]],2));
			if(d > temp){
				d = temp;
				*pt1 = P3[i];
				*pt2 = P3[j];
			}
		}
	}
	return d;
}