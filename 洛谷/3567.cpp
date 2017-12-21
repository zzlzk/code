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

#define MAXN 500010

struct Chairman_Tree {
	int ch[2],sum;
};

int root[MAXN],tot;
Chairman_Tree t[MAXN*20];

#define lc t[now].ch[0]
#define rc t[now].ch[1]
#define lson lc,l,mid
#define rson rc,mid+1,r

void modify(int pre,int &now,int l,int r,int pos,int x) {
	t[now=++tot]=t[pre],t[now].sum+=x;
	if(l==r) return;
	int mid=l+r>>1;
	if(pos<=mid) modify(t[pre].ch[0],lson,pos,x);
	else modify(t[pre].ch[1],rson,pos,x);
	return;
}

int query(int pre,int now,int l,int r,int k) {
	if(l==r) return l;
	int mid=l+r>>1;
	if(t[lc].sum-t[t[pre].ch[0]].sum>k)
		return query(t[pre].ch[0],lson,k);
	if(t[rc].sum-t[t[pre].ch[1]].sum>k)
		return query(t[pre].ch[1],rson,k);
	return 0;
}

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1,x;i<=n;i++) 
		input(x),modify(root[i-1],root[i],1,n,x,1);
	for(int l,r;m;m--) {
		input(l),input(r);
		printf("%d\n",query(root[l-1],root[r],1,n,r-l+1>>1));
	}
	return 0;
}
