#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>

#define FOR(A,B,C) for(int A=B;A<C;A++)
#define EFOR(A,B,C) for(int A=B;A<=C;A++)
#define RFOR(A,B,C) for(int A=B;A>=C;A--)
#define MEM(A,B) memset(A,B,sizeof(A))

using namespace std;

struct tNode {
	int val;
	struct tNode *left,*right;
	tNode(int v, tNode *lf,tNode *rt){
		val=v;
		left=lf,right=rt;
	}
};

void inOrder(tNode *root)
{
	if(root==NULL)
		return;

	inOrder(root->left);
	cout<<root->val<<" ";
	inOrder(root->right);
}

tNode* LCABst(tNode *root,int a,int b)
{
	if(a>b)		swap(a,b);
	if(root==NULL)		return NULL;

	if(a==root->val || root->val==b || (a<root->val && root->val<b))
		return root;

	if(root->val<a)
		return LCABst(root->right,a,b);

	return LCABst(root->left,a,b);
}

//	LCA in binary tree
tNode* LCA(tNode *root,tNode *p,tNode *q)
{
	if(!root)
		return NULL;

	if(root==p || root==q)
		return root;

	tNode *L=LCA(root->left,p,q);
	tNode *R=LCA(root->right,p,q);

	if(L && R)
		return root;

	return L?L:R;
}

bool inRange(tNode *root,int mn,int mx)
{
	if(root==NULL)		return 1;
	if(root->val<mn || mx<root->val)		return 0;

	return inRange(root->left,mn,root->val) &&
			inRange(root->right,root->val,mx);
}

bool isBst(tNode *root)
{
	return inRange(root,INT_MIN,INT_MAX);
}

void levelSpiralStk(tNode *root)
{
	stack<tNode*>st[2];

	st[0].push(root);
	int level=0;

	while(!st[level&1].empty()){
		int use=level&1;
		while(!st[use].empty()){
			tNode *cur=st[use].top();
			st[use].pop();

			if(cur==NULL)
				continue;

			cout<<cur->val<<" ";
			//	Order is determined by level
			tNode *fir=(use)?cur->left:cur->right;
			tNode *sec=(use)?cur->right:cur->left;
			st[!use].push(fir);
			st[!use].push(sec);
		}
		level++;
	}
	cout<<"\n";
}

void levelSpiralDq(tNode *root)
{
	deque<tNode*>q;
	q.push_back(root);

	int cur=1,level=1;
	while(!q.empty()){
		int next=0;
		while(cur--){
			tNode *now;
			if(level&1){
				now=q.back();
				q.pop_back();
			} else {
				now=q.front();
				q.pop_front();
			}

			if(now==NULL)
				continue;

			cout<<now->val<<" ";
			if(level&1){
				q.push_front(now->right);
				q.push_front(now->left);
			} else {
				q.push_back(now->left);
				q.push_back(now->right);
			}
			next+=2;
		}
		cur=next,level++;
	}
	cout<<"\n";
}

void inOrderStk(tNode *root)
{
	stack<tNode*>sk;
	while(!sk.empty() || root!=NULL){
		if(root==NULL){
			root=sk.top();
			sk.pop();
			cout<<root->val<<" ";
			root=root->right;
		} else {
			sk.push(root);
			root=root->left;
		}
	}
	cout<<"\n";
}

void preOrderStk(tNode *root)
{
	stack<tNode*>sk;
	sk.push(root);
	while(!sk.empty()){
		tNode *now=sk.top();
		sk.pop();
		if(now==NULL)
			continue;

		cout<<now->val<<" ";
		sk.push(now->right);			//	Opposite order
		sk.push(now->left);
	}
	cout<<"\n";
}

void postOrderStk(tNode *root)
{
	stack<tNode*>sk;
	sk.push(root);
	while(!sk.empty()){
		tNode *now=sk.top();
		sk.pop();

		if(now==NULL)
			continue;

		bool done=true;
		if(sk.empty() || now!=sk.top())
			done=false;

		if(done){
			cout<<now->val<<" ";
			sk.pop();
		} else {
			sk.push(now);
			sk.push(now);				//	Push twice as marker
			sk.push(now->right);
			sk.push(now->left);
		}
	}
}

void MorrisTraversal(tNode *root)
{
	tNode *predc;
	while(root!=NULL){
		if(root->left==NULL){
			cout<<root->val<<" ";		//	Prints all elements with no right child
			root=root->right;			//	Either its successor has been set
										//	as its right or it is the last element
			continue;
		}

		for(predc=root->left;predc->right!=NULL && predc->right!=root;predc=predc->right);

		if(predc->right==NULL){
			predc->right=root;
			root=root->left;
		} else {
			predc->right=NULL;
			cout<<root->val<<" ";
			root=root->right;
		}
	}
	cout<<"\n";
}

tNode* recSuc(tNode *root,tNode *target)
{
	if(root==target || root==NULL)
		return NULL;

	if(root->val<target->val)
		return recSuc(root->right,target);
	else {
		tNode *tmp=recSuc(root->left,target);
		return (tmp!=NULL)?tmp:root;
	}
}

tNode* inOrdSuc(tNode *root,tNode *target)
{
	if(root==NULL)
		return NULL;

	if(target->right!=NULL){
		tNode *tmp=target->right;
		for(;tmp->left!=NULL;tmp=tmp->left);
		return tmp;
	}
	return recSuc(root,target);
}

class InorderIterator{
	tNode* current;
	stack<tNode*>S;

	InorderIterator(tNode *root){
		current=root;

		if(current==NULL)
			return;

		S.push(NULL);
		while(current->left!=NULL){
			S.push(current);
			current=current->left;
		}
	}

	tNode* getCurrent(){
		return current;
	}

	tNode* next(){
		if(current==NULL)
			return NULL;

		if(current.right!=NULL){
			current=current->right;
			while(current->left!=NULL){
				S.push(current);
				current=current->left;
			}
		} else {
			current=S.top();
			S.pop();
		}
		return getCurrent();
	}
};

int main()
{
	tNode *two=new tNode(2,NULL,NULL);
	tNode *one=new tNode(1,NULL,two);
	tNode *fr=new tNode(4,NULL,NULL);
	tNode *thr=new tNode(3,one,fr);
	tNode *twe=new tNode(20,NULL,NULL);
	tNode *ten=new tNode(10,NULL,NULL);
	tNode *tsix=new tNode(26,twe,NULL);
	tNode *ele=new tNode(11,ten,tsix);
	tNode *root=new tNode(9,thr,ele);

	tNode *suc=inOrdSuc(root,tsix);
	cout<<((suc!=NULL)?suc->val:-1)<<"\n";

	postOrderStk(root);

	getchar();
	return 0;
}
