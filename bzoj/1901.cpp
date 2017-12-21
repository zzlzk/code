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

#define MAXN 10010
#define MAXM 10010

struct Chairman_Tree {
	int ch[2],sum;
};

int tot,n,m,root[MAXN];
Chairman_Tree t[MAXN*600];

int a[MAXN],b[MAXN+MAXM],c[MAXN+MAXM],rank,cnt;

int lowbit(int x) {
	return x&(-x);
}

#define lc t[now].ch[0]
#define rc t[now].ch[1]
#define lson lc,l,mid
#define rson rc,mid+1,r

void discretization() {
	sort(b+1,b+cnt+1);
	c[rank=1]=b[1];
	for(int i=2;i<=cnt;i++)
		if(b[i]!=b[i-1])
			c[++rank]=b[i];
	return;
}

int Lower_bound(int x) {
	int l=1,r=rank;
	while(l<=r) {
		int mid=l+r>>1;
		if(c[mid]<x) l=mid+1;
		else r=mid-1;
	}
	return l;
}

void modify(int pre,int &now,int l,int r,int pos,int x) {
	t[now=++tot]=t[pre],t[now].sum+=x;
	if(l==r) return;
	int mid=l+r>>1;
	if(pos<=mid) modify(t[pre].ch[0],lson,pos,x);
	else modify(t[pre].ch[1],rson,pos,x);
	return;
}

void modify(int k,int x) {
	int pos=Lower_bound(a[k]);
	for(int i=k;i<=n;i+=lowbit(i))
		modify(root[i],root[i],1,rank,pos,x);
	return;
}

struct Operation {
	int op,l,r,k;
};

Operation o[MAXM];
int p[MAXN],q[MAXN],cntp,cntq;

int query(int l,int r,int k) {
	if(l==r) return l;
	int sum=0,mid=l+r>>1;
	for(int i=1;i<=cntp;i++)
		sum-=t[t[p[i]].ch[0]].sum;
	for(int i=1;i<=cntq;i++)
		sum+=t[t[q[i]].ch[0]].sum;
	if(k<=sum) {
		for(int i=1;i<=cntp;i++)
			p[i]=t[p[i]].ch[0];
		for(int i=1;i<=cntq;i++)
			q[i]=t[q[i]].ch[0];
		return query(l,mid,k);
	} else {
		for(int i=1;i<=cntp;i++)
			p[i]=t[p[i]].ch[1];
		for(int i=1;i<=cntq;i++)
			q[i]=t[q[i]].ch[1];
		return query(mid+1,r,k-sum);
	}
}

int query(Operation z) {
	cntp=cntq=0;
	for(int i=z.l-1;i;i-=lowbit(i))
		p[++cntp]=root[i];
	for(int i=z.r;i;i-=lowbit(i))
		q[++cntq]=root[i];
	return c[query(1,rank,z.k)];
}

int modify(Operation z) {
	modify(z.l,-1);
	a[z.l]=z.k;
	modify(z.l,1);
	return 0;
}

int main() {
	input(n),input(m);
	for(int i=1;i<=n;i++)
		input(a[i]),b[++cnt]=a[i];
	char op[3];
	for(int i=1;i<=m;i++) {
		scanf("%s",op);
		if(op[0]=='Q') {
			input(o[i].l),input(o[i].r),input(o[i].k);
			o[i].op=1;
		} else {
			input(o[i].l),input(o[i].k);
			o[i].op=0,b[++cnt]=o[i].k;
		}
	}
	discretization();
	for(int i=1;i<=n;i++)
		modify(i,1);
	for(int i=1;i<=m;i++)
		o[i].op?printf("%d\n",query(o[i])):modify(o[i]);
	return 0;
}
