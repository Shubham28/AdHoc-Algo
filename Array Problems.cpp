#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stack>
#include <utility>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))
#define PII pair<int,int>

using namespace std;

//	Count pairs with sum=K
int countPair(int *ar, int L,int K)
{
	sort(ar,ar+L);

	int tot=0,lhs,rhs;
	for(int lft=0,rt=L-1;lft<rt;){
		int S=ar[lft]+ar[rt];

		if(S==K){
			if(ar[lft]==ar[rt]){
				int tmp=rt+1-lft;
				tot+=((tmp*(tmp-1))/2);
			} else {
				lhs=rhs=1;
				while(ar[lft]==ar[lft+1])		lhs++,lft++;
				while(ar[rt]==ar[rt-1])			rhs++,rt--;

				tot+=(lhs*rhs);
				lft++,rt--;
			}
		} else if(S<K)		lft++;
		else if				rt--;
	}
	return 0;
}


int main()
{
	int inp[] = {1,4,11,3,10,10,26,9};

	findPair(inp,sizeof(inp)/sizeof(int),8);

	cin>>inp[0];
	return 0;
}
