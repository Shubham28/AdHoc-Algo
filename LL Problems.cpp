#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <list>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))

using namespace std;

struct node {
	int val;
	struct node* next;
	node(int v, node *nx){
		val=v;
		next=nx;
	}
};

int getNth(node *root,int ind)			//	1-based
{
	int done=1;							//	Start with 1 & return inside loop
	while(root!=NULL){
		if(ind==done)
			return root->val;

		root=root->next;
		done++;
	}
	return -1;
}

int getNthLast(node *root,int ind)
{
	node *fast=root;

/*	Special case: When 1st element is to be returned, fast will be NULL & it is also
	NULL when ind is greater than length	*/

	for(int inc=1;inc<ind && fast!=NULL;inc++)
		fast=fast->next;

	if(fast==NULL)
		return -1;

	fast=fast->next;
	while(fast!=NULL){
		fast=fast->next;
		root=root->next;
	}
	return root->val;
}

int getMiddle(node *root)
{
	if(root==NULL)
		return -1;

	node *slow=root,*fast=root->next;
	while(fast!=NULL){
		fast=fast->next;

		if(fast!=NULL){
			slow=slow->next;
			fast=fast->next;
		}
	}
	return slow->val;
}

void deleteList(node *root)
{
	node *tmp;
	while(root!=NULL){
		tmp=root->next;
		delete root;
		root=tmp;
	}
	return;
}

//	Iterative reverse
node* reverseList(node *root)
{
	node *result=NULL;				//	Handles last node pointing to NULL case
	node *rest=root;

	node *tmp;
	while(rest!=NULL){
		tmp=rest->next;

		rest->next=result;
		result=rest,rest=tmp;
	}
	return result;
}

//	Recursive reverse
node* reverseListRec(node *root)
{
	if(root==NULL || root->next==NULL)
		return root;

	node *rest=reverseListRec(root->next);

	root->next->next=root;
	root->next=NULL;

	return rest;
}

node *start;
bool checkRev(node *root)
{
	if(root->next==NULL)
		return (start->val==root->val);

	bool res=checkRev(root->next);
	if(res){
		start=start->next;
		res=(start->val==root->val);
	}
	return res;
}

bool isPalin(node *root)
{
	if(root==NULL || root->next==NULL)
		return 1;

	start=root;
	return checkRev(root);
}

struct randomPtr {
	int val;
	randomPtr *next,*rnd;

	randomPtr(int v, randomPtr *n, randomPtr *r){
		val=v;
		next=n,rnd=r;
	}
};

randomPtr* copyRnd(randomPtr *root)
{
	if(root==NULL)
		return NULL;

	randomPtr *tmp=root;
	while(tmp!=NULL){
		randomPtr *ins=new randomPtr(tmp->val,tmp->next,NULL);
		tmp->next=ins;
		tmp=ins->next;
	}

	randomPtr *ret=root->next;

	tmp=root;
	while(tmp!=NULL){
		randomPtr *ins=tmp->next;
		ins->rnd=tmp->rnd->next;

		tmp=ins->next;
	}

	tmp=root;
	while(tmp!=NULL){
		randomPtr *ins=tmp->next;

		tmp->next=ins->next;
		tmp=tmp->next;

		if(tmp!=NULL)					//	Condition for last node
			ins->next=tmp->next;

	}
	return ret;
}

node* removeDuplSort(node *root)
{
	if(root==NULL)
		return root;

	node *ret=root;
	while(root->next!=NULL){
		node *tmp=root->next;

		if(tmp->val==root->val){
			root->next=tmp->next;
			delete tmp;
		} else
			root=root->next;
	}
	return ret;
}

node* revAltK(node *root,int K)
{
	if(root==NULL)
		return root;

	int cnt=0;
	node *head=root;				//	Keep track of initial head
	node *result=NULL,*cur=root;		//	Start from NULL

	while(cur!=NULL && cnt<K){
		node *nxt=cur->next;
		cur->next=result;

		result=cur,cur=nxt;
		cnt++;
	}
	head->next=cur;					//	cur is actually next

	cnt=1;
	while(cnt<K && cur!=NULL){
		cur=cur->next;
		cnt++;
	}
	if(cur!=NULL)
		cur->next=revAltK(cur->next,K);

	return result;				//	prev becomes head at the end of 1st iteration
}

void removeLoop(node *head, node *meet)
{
	node *start=head;
	while(start!=meet){
		start=start->next;
		meet=meet->next;
	}

	node *last=meet;
	while(last->next!=meet)
		last=last->next;

	last->next=NULL;
	return;
}

int detectAndRemoveLoop(node *head)
{
	node *slow=head,*fast=head;
	while(fast!=NULL && fast->next!=NULL){
		slow=slow->next;
		fast=fast->next->next;

		if(slow==fast){
			removeLoop(head,slow);
			return 1;
		}
	}
	return 0;
}

/*	LRU Cache with doubly LL & Hash table

void ReferencePage(queue* qu, Hash* hash, unsigned pageNumber)
{
   	QNode* reqPage = hash->array[pageNumber];

    if ( reqPage == NULL )
   	    Enqu( qu, hash, pageNumber );

   	// page is there and not at front, change pointer
    else if (reqPage != qu->front){
		reqPage->prev->next = reqPage->next;

        if (reqPage->next)
           reqPage->next->prev = reqPage->prev;

        // If the requsted page is rear, then change rear
        // as this node will be moved to front
        if (reqPage == qu->rear)
           qu->rear = reqPage->prev;

        // Put the requsted page before current front
        reqPage->next = qu->front;
        reqPage->prev = NULL;

        // Change prev of current front
        reqPage->next->prev = reqPage;

        // Change front to the requsted page
        qu->front = reqPage;
    }
}
*/

const int L=5;
map<int, list<int>::iterator >hashMap;
list<int>cacheLL;

void initLRUCache()
{
	hashMap.clear();
	cacheLL.clear();
}

void addToCache(int id, bool check)
{
	cacheLL.push_back(id);
	hashMap[id]=--(cacheLL.end());

	if(check && cacheLL.size()>L){
		int id=cacheLL.front();
		cacheLL.pop_front();
		hashMap.erase(id);
	}
}

void pushToCache(int id)
{
	map<int, list<int>::iterator >::iterator position=hashMap.find(id);
	if(position==hashMap.end()){
		addToCache(id,true);
	}
	else {
		list<int>::iterator location=(*position).second;
		cacheLL.erase(location);
		hashMap.erase(id);
		addToCache(id,false);
	}
	for(list<int>::iterator it=cacheLL.begin();it!=cacheLL.end();it++)
		cout<<(*it)<<" ";
	cout<<"\n";
}

/*	2 LL represnting numbers are given. Sum of them, in-place
	e.g 1 - 2 - 3 (321)
		4 - 5 - 7 - 9 (9754)		=	5 - 7 - 0 - 0 - 1	*/

void addTwoNumbers()
{
	int inp[][4]={{1,2,3,-1},{4,5,7,9}};
	node *num[2];

	FOR(d,0,2){
		node *last=NULL;
		for(int i=0;i<4 && inp[d][i]!=-1;i++){
			node *tmp=new node(inp[d][i],NULL);

			if(last==NULL)		num[d]=last=tmp;
			else{
				last->next=tmp;
				last=last->next;
			}
		}
	}

	node *ans,*last=NULL,*temp;

	int res,carry=0;
	while(num[0]!=NULL || num[1]!=NULL){
		res=(num[0]?num[0]->val:0)+(num[1]?num[1]->val:0)+carry;

		if(res>=10)
			res-=10,carry=1;

		temp=new node(res,NULL);
		if(last==NULL)
			ans=last=temp;
		else{
			last->next=temp;
			last=temp;
		}

		if(num[0])	num[0]=num[0]->next;
		if(num[1])	num[1]=num[1]->next;
	}
	if(carry)
		last->next=new node(carry,NULL);

	while(ans!=NULL){
		cout<<ans->val<<" ";
		ans=ans->next;
	}
	cout<<"\n";
}

int main()
{
	int inp[] = {1,4,11,3,10,26,9};
	node *root = NULL;

/*	node *last,*mid;
	RFOR(i,sizeof(inp)/sizeof(int)-1,0){
		node* tmp=new node(inp[i],root);
		root=tmp;

		if(tmp->next==NULL)		last=tmp;
		if(tmp->val==10)
			mid=tmp;
	}
	last->next=mid;
	detectAndRemoveLoop(root);

	node *ans=root;
	while(ans!=NULL){
		cout<<ans->val<<" ";
		ans=ans->next;
	}
	cout<<"\n";
*/

	initLRUCache();
	int chk;
	cin>>chk;
	while(chk!=-1){
		pushToCache(chk);
		cin>>chk;
	}

	return 0;
}
