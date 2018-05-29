#include<stdio.h>
#include<math.h>
#define MINIMUM(a,b) (a<b ? a:b)

void   Sort_by_X_or_Y ( double *A, unsigned int *P, unsigned int N ){
  // input  : A[] (x or y position array of N points)
  //          P[] (index array of X (initital) or Y (during combine))
  //          N   number of points to sort
  // output : P[] (the indices are sorted by x or y position)
	int temp;

	for(unsigned int i=0; i<N-1; i++)
		for(unsigned int j=i+1; j<N; j++)
			if(A[P[i]]>A[P[j]]){
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
			}

	//if N > THR 내가 정함
			//quick sort
			
	//else
			//O(n^2)
}		

void Merge_by_Y(double *Y, unsigned int L,	unsigned int R, unsigned int *P2, unsigned int *P3){
	// merge P2 into P3 with O(nlogn) algorithm. (n = the number of elments in P2)
	
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
		for(unsigned int i=L; i<=R; i++)	P2[i] = P1[i];
		if(R == L)	return min;
		else if(R-L == 1)
			if(Y[P2[L]] > Y[P2[R]]){
				int temp;
				temp = P2[L];
				P2[L] = P2[R];
				P2[R] = temp;
			}
		else{
			int temp;
			for(unsigned int i=L; i<=R-1; i++)
				for(unsigned int j=i+1; j<=R; j++)
					if(Y[P2[i]] > Y[P2[j]]){
					temp = P2[i];
					P2[j] = P2[i];
					P2[i] = temp;
					}
		}
		return min;
	}
	double CPl, CPr, CPc, d=min;
	int tmpPt1, tmpPt2;
	//P1 x축기준 오름차순 정렬되있는 상태
	
	CPl = Closest_Pair_DC(L,(L+R)/2,pt1,pt2,X,Y,P1,P2,P3,THR);
	tmpPt1 = *pt1;
	tmpPt2 = *pt2;
	CPr = Closest_Pair_DC((L+R)/2+1,R,pt1,pt2,X,Y,P1,P2,P3,THR);
	if(CPr > CPl){	
		*pt1 = tmpPt1;
		*pt2 = tmpPt2;
	}
	d = MINIMUM(CPl,CPr);
	//P3는 sort하는것이아니라 이미 sort되어있는 P2를 merge만 한다.
	Merge_by_Y(Y,L,R,P2,P3);
	//P2 <- P3   (전단계를 위해 정렬해둔다)
	for(unsigned int i=L; i<=R; i++)	P2[i] = P3[i];
	//P2 -> P3 (중간영역만)
	int tmp = 0;
	for(unsigned int i=L; i<=R; i++){
		if(((X[P1[(L+R)/2]]-d) < X[P2[i]] && P2[i] <= (L+R)/2) || ((X[P1[(L+R)/2+1]] + d) > X[P2[i]] && P2[i] >= (L+R)/2+1))
			P3[tmp++] = P2[i];
	}
	//find CPc
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
