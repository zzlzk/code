#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
	x=0; T a=1;
	register char c=getchar();
	for(;c<48||c>57;c=getchar())
		if(c==45) a=-1;
	for(;c>=48&&c<=57;c=getchar())
		x=x*10+c-48;
	x*=a;
	return;
}

#define MAXN 1000010

struct Chairman_Tree {
	int ch[2],sum;
};

int a[MAXN],tot,root[MAXN];
Chairman_Tree t[MAXN*20];

#define lc t[now].ch[0]
#define rc t[now].ch[1]
#define lson lc,l,mid
#define rson rc,mid+1,r

void build(int &now,int l,int r) {
	now=++tot;
	if(l==r) {
		t[now].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	build(lson),build(rson);
	return;
}

void modify(int pre,int &now,int l,int r,int pos,int x) {
	t[now=++tot]=t[pre];
	if(l==r) {
		t[now].sum=x;
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid) modify(t[pre].ch[0],lson,pos,x);
	else modify(t[pre].ch[1],rson,pos,x);
	return;
}

int query(int now,int l,int r,int pos) {
	if(l==r) return t[now].sum;
	int mid=l+r>>1;
	if(pos<=mid) return query(lson,pos);
	return query(rson,pos);
}

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1;i<=n;i++)
		input(a[i]);
	build(root[0],1,n);
	for(int op,loc,value,v,i=1;i<=m;i++) {
		input(v),input(op);
		if(op==1) {
			input(loc),input(value),
			modify(root[v],root[i],1,n,loc,value);
		} else {
			input(loc),root[i]=root[v];
			printf("%d\n",query(root[v],1,n,loc));
		}
	}
	return 0;
}
