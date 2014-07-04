#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <list>
#include <utility>
#include <climits>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))
#define PII pair<int,int>

using namespace std;

void permRec(char *inp, int L, int indx)
{
	if(indx==L-1){
		printf("%s\n",inp);
		return;
	}

	FOR(sw,indx,L){
		swap(inp[indx],inp[sw]);
		permRec(inp,L,indx+1);
		swap(inp[indx],inp[sw]);
	}
}

//	e.g gggeeeksss -> geks
void removeDupl(char *inp, int L)
{
	bool pres[256];
	MEM(pres,0);

	int use=0;
	FOR(st,0,L)
		if(!pres[int(inp[st])]){
			pres[int(inp[st])]=1;
			inp[use++]=inp[st];
		}

	inp[use]=0;
	cout<<inp<<"\n";
}

//	Checks if the given string is input's string rotation
bool isRotation(char *inp, int L, char *chk)
{
	char repeat[2*L+1];
	repeat[0]=0;

	strcat(repeat,inp);
	strcat(repeat,inp);

	//	Uses strstr - returns pointer to the matching substring position
	return (strstr(repeat,chk)!=NULL);
}

bool isContained(char *inp, int L, char super[], int T)
{
	if(L>T)	return 0;

/*	size_t strspn( const char *dest, const char *src);
	Returns the length of the maximum initial segment of the byte string
	pointed to by dest, that consists of only the characters found in byte string pointed to by src. */

	return (strspn(inp,super)==L);
}

void reverseWords(char *inp, int L)
{
	int st=0;
	EFOR(i,0,L)
		if(i==L || inp[i]==' '){
			reverse(inp+st,inp+i);
			st=i+1;
		}

	reverse(inp,inp+L);
	cout<<inp<<"\n";
}

void runLengthEncode(char *inp, int L)
{
	char res[L+1],tmp[5];
	MEM(res,0);

	char prev=inp[0];
	int cnt=1;
	EFOR(i,1,L){
		if(i==L || inp[i]!=inp[i-1]){
			sprintf(tmp,"%c%d",inp[i-1],cnt);		//	Number can be >1 digit
			strcat(res,tmp);

			prev=inp[i],cnt=1;
		} else
			cnt++;
	}
	cout<<res<<"\n";
}

/*	Finding the Minimum Window in S which Contains All Elements from T
	Has a O( S*log(T) ) & O(S) solution.
	http://leetcode.com/2010/11/finding-minimum-window-in-s-which.html */

void minWindow(char *S, int lenS, char *T, int lenT)
{
	int needToFind[256] = {0};
	FOR(i,0,lenT)
		needToFind[T[i]]++;

	int hasFound[256] = {0};

	int first=0,last=0,found=0;
	int frWind,toWind,minLen=INT_MAX;

	for(;first<=last && last<lenS;last++){
		int prs=int(S[last]);
		hasFound[prs]++;

		if(needToFind[prs]==0)
			continue;

		if(hasFound[prs]==needToFind[prs])
			found++;

		if(found==lenT){
			while(hasFound[S[first]]>needToFind[S[first]]){
				hasFound[S[first]]--;
				first++;
			}

			if(minLen>(last+1-first)){
				minLen=last+1-first;
				frWind=first,toWind=last;
			}
		}
	}
	cout<<frWind<<","<<toWind<<" -> "<<minLen<<"\n";

	return;
}

void longestUniqueSubst(char inp[], int L)
{
	int vist[256];
	MEM(vist,-1);

	vist[inp[0]]=0;
	int start=0,fr=0,best=1;
	FOR(i,1,L){
		char now=inp[i];

		if(vist[now]==-1 || vist[now]<start){
			if(best<i+1-start){
				best=i+1-start;
				fr=start;
			}
		} else {
			if(best<i-vist[now]){
				best=i-vist[now];
				fr=vist[now]+1;
			}
			start=vist[now]+1;
		}
		vist[now]=i;
	}
	printf("Best length starts at %d, length %d\n",fr,best);

	return;
}

void genPermIter(char inp[], int L)
{
	sort(inp,inp+L);
	printf("%s\n",inp);

	while(true){
		int fr=-1,to;
		RFOR(i,L-2,0)
			if(inp[i]<inp[i+1]){
				fr=i;
				break;
			}

		if(fr==-1)
			return;

		RFOR(i,L-1,fr+1)
			if(inp[fr]<inp[i]){
				to=i;
				break;
			}

		swap(inp[fr],inp[to]);
		reverse(inp+fr+1,inp+L);

		printf("%s\n",inp);
	}
}

//	Eliminate all 'b' and 'ac' in the string. Replace them in-place & in 1 iteration of string
void eliminateStr()
{
	char str[10];
	scanf("%s",str);
	int L=strlen(str);

	int write=0;
	FOR(pos,0,L)
		if(str[pos]!='b'){
			if(str[pos]=='c'){
				if(write>0 && str[write-1]=='a')
					write--;
				else
					str[write++]='c';
			} else
				str[write++]=str[pos];
		}

	str[write]='\0';
	printf("%s\n",str);
}

int main()
{
	char inp[]="abcc";
	int L=strlen(inp);

//	FOR(i,0,10)
//	eliminateStr();

	return 0;
}
