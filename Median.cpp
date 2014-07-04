#include<stdio.h>
 
int median(int arr[], int N)
{
	if(N%2 == 0)
		return (arr[N/2]+arr[N/2-1])/2;
	else
		return arr[N/2];
}

int max(int x, int y)
{	return x > y? x : y;	}
 
int min(int x, int y)
{	return x > y? y : x;	}
 
/*	This function returns median of ar1[] and ar2[].
	Both ar1[] and ar2[] are sorted arrays & Both have N elements	*/

int getMedian(int ar1[], int ar2[], int N)
{
	int m1;													//	Median of ar1
	int m2;													// Median of ar2

	if(N<=0)
		return -1;

	if(N==1)
		return (ar1[0] + ar2[0])/2;

	if(N==2)
		return (max(ar1[0],ar2[0]) + min(ar1[1],ar2[1]))/2;

	m1=median(ar1,N);
	m2=median(ar2,N);
 
	// If medians are equal then return either m1 or m2
	if(m1==m2)
		return m1;

//	If m1 < m2 then median must exist in ar1[m1....] and ar2[....m2]
	if(m1<m2){
		if(N%2==0)
			return getMedian(ar1+N/2-1,ar2,N-N/2+1);
	else
		return getMedian(ar1+N/2,ar2,N-N/2);
	}

	if(N%2==0)
		return getMedian(ar2+N/2-1,ar1,N-N/2+1);
	else
		return getMedian(ar2+N/2,ar1,N-N/2);

}
 
int main()
{
	int ar1[]={2,4,6,10};
	int ar2[]={1,3,9,12};
	printf("%d\n", getMedian(ar1,ar2,4)) ;

	getchar();
	return 0;
}
