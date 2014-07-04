#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <set>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))
#define ALL(A) A.begin(),A.end()
#define SZ(A) int(A.size())
#define LL long long

using namespace std;

//	http://www2.myoops.org/course_material/mit/NR/rdonlyres/Electrical-Engineering-and-Computer-Science/6-046JFall-2005/30C68118-E436-4FE3-8C79-6BAFBB07D935/0/ps9sol.pdf

double findMedian(int A[],int B[],int l,int r,int nA,int nB)
{
	if(l>r)
		return findMedian(B,A,0,nB,nB,nA);

	int i=(l+r)/2;
	int j=(nA+nB)/2-i-1;

	if(j>=0 && A[i]<B[j])
		return findMedian(A,B,i+1,r,nA,nB);

	if(j<nB-1 && A[i]>B[j+1])
		return findMedian(A,B,l,i-1,nA,nB);

	if((nA+nB)%2==1)
		return A[i];

	if(i>0)
		return(A[i]+max(B[j],A[i-1]))/2.0;

	return (A[i]+B[j])/2.0;
}

double findMedianSortedArrays(int A[],int n,int B[],int m) {
	if(n<m)
		return findMedian(A,B,0,n-1,n,m);
	return findMedian(B,A,0,m-1,m,n);
}

//	http://leetcode.com/2011/01/find-k-th-smallest-element-in-union-of.html

int findKthSmallest(int A[],int aLen,int B[],int bLen,int K)
{
	int i=(K*aLen)/(aLen+bLen+0.0);
	int j=K-1-i;

	int aPrev=(i==0)?INT_MIN:A[i-1];
	int bPrev=(j==0)?INT_MIN:B[j-1];
	int aCur=(i==aLen)?INT_MAX:A[i];
	int bCur=(j==bLen)?INT_MAX:B[j];

	if(bPrev<aCur && aCur<bCur)
		return aCur;
	if(aPrev<bCur && bCur<aCur)
		return bCur;

	if(aCur<bPrev)
		return findKthSmallest(A+i+1,aLen-i-1,B,j,K-i-1);

	return findKthSmallest(A,i,B+j+1,bLen-j-1,K-j-1);
}

int main()
{
	//	{1,3,4,7,8,10,12,13,16,17,19}
	int A[]={4,8,12,16,17},aLen=5;
	int B[]={1,3,7,10,13,19},bLen=6;

	cout<<findKthSmallest(A,aLen,B,bLen,6)<<"\n";
//	cout<<findMedianSortedArrays(A,aLen,B,bLen)<<"\n";

	return 0;
}
