#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <utility>
#include <map>
#include <vector>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))
#define PII pair<int,int>

using namespace std;

struct entry{
	int val,pos;
};

struct entryCompr{
	bool operator() (const entry &lhs, const entry &rhs) const{
		if(lhs.val!=rhs.val)
			return lhs.val>rhs.val;

		return lhs.pos>rhs.pos;
	}
};

/*	------------------------------------------------------------------------------------------------
	There are N people standing in queue. Every person knows the number of taller people before him.
	After Queue is dispersed, find a way to form the same queue.
	Codeforces 141C. Queue
	http://tsenmu.com/blog/?p=26
*/

struct Item
{
	string name;
	int a; //the number of people who are higher and stand in the queue in front of person
};

bool cmp(const Item& a, const Item& b)
{
	return a.a<b.a;
}

const int N_MAX=1001;
Item items[N_MAX];
int heightOrder[N_MAX];
int height[N_MAX];

int reprodQueue()
{
	int n;
	scanf("%d", &n);
	FOR(i,0,n)
		cin>>items[i].name>>items[i].a;

	sort(items,items+n,cmp);
	bool error=false;
	FOR(i,0,n){

		if(items[i].a>i) {
			error=true;
			break;
		}

		for(int j=i-1;j>=items[i].a;--j) {
			// Shifting to empty the place in items[i].a+1
			heightOrder[j+1]=heightOrder[j];
		}
		heightOrder[items[i].a]=i; // Fill items[i].a with i
	}

	FOR(i,0,n){
		// Calculating the height according to the height order
		height[heightOrder[i]]=n-i;
	}

	if(error) {
		printf("-1\n");
	} else {
		FOR(i,0,n)
			cout<<items[i].name<<" "<<height[i]<<endl;
	}
}

//	----------------------------------------------------------------------------------------

bool checkMajor(int ar[],int N,int req,int chk)
{
	int tot=0;
	FOR(i,0,N)
		if(ar[i]==chk)
			tot++;

	return (tot>req);
}

//	Find the majority element

void findMajority()
{
	int ar[100];
	int N;
	cin>>N;

	FOR(i,0,N)
		cin>>ar[i];

	int maj=ar[0],cnt=1;
	FOR(i,0,N){
		if(maj==ar[i])
			cnt++;
		else
			cnt--;

		if(cnt==0)
			maj=ar[i],cnt=1;
	}
	if(checkMajor(ar,N,N/2,maj))
		printf("%d\n",maj);
}

/*	Given a list of n elements in an array, finds all the elements that appear more than n/3 times in the list.
	Expected is O(n).	*/

void modMajority()
{
	int ar[100];
	int N;
	cin>>N;

	FOR(i,0,N)
		cin>>ar[i];

	int maj[2],cnt[]={0,0};

	FOR(i,0,N){

		bool fnd=0;
		FOR(chk,0,2)
			if(maj[chk]==ar[i]){
				cnt[chk]++;
				fnd=1;
			}

		if(!fnd){
			FOR(chk,0,2)
				if(cnt[chk]==0){
					maj[chk]=ar[i],cnt[chk]=1,fnd=1;
					break;
				}

			if(!fnd){
				cnt[0]--,cnt[1]--;
				if(cnt[0]==0)
					maj[0]=ar[i],cnt[0]=1;
				else if(cnt[1]==0)
					maj[1]=ar[i],cnt[1]=1;
			}
		}
	}

	FOR(i,0,2)
		if(checkMajor(ar,N,N/3,maj[i]))
			printf("%d\n",maj[i]);
}

//	----------------------------------------------------------------------------------------

//	Largest rectangle in histogram

void largRect()
{
	int hist[100];
	int N,mx=0;
	cin>>N;

	FOR(i,0,N)
		cin>>hist[i];

	stack< PII >incrs;
	EFOR(i,0,N){

		while(!incrs.empty() && (i==N || hist[i]<incrs.top().second)){
			PII now=incrs.top();
			incrs.pop();
			int left=-1;

			if(!incrs.empty())
				left=incrs.top().first;

			mx=max(mx,(i-1-left)*now.second);
		}

		if(i<N)
			incrs.push(PII(i,hist[i]));
	}
	printf("%d\n",mx);
}

//	----------------------------------------------------------------------------------------

int main()
{
	int inp[] = {19,4,11,3,10,26,9};
	entry ar[7];
	FOR(i,0,7)
		ar[i].pos=i,ar[i].val=inp[i];

	findMajority();

	return 0;
}
