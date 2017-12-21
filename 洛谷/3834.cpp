#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
	x=0; T a=1;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	x*=a;
	return;
}

#define MAXN 200010

struct Data {
	int x,id;
	Data(int x=0,int id=0):
		x(x),id(id) {}
	bool operator < (const Data &q) const {
		return x<q.x;
	}
};

Data a[MAXN];
int b[MAXN],c[MAXN];

struct Chairman_Tree {
	int ch[2],sum;
};

Chairman_Tree t[MAXN*20];
int root[MAXN],tot;

#define lc t[now].ch[0]
#define rc t[now].ch[1]
#define lson lc,l,mid
#define rson rc,mid+1,r

void build(int &now,int l,int r) {
	now=++tot;
	if(l==r) return;
	int mid=l+r>>1;
	build(lson),build(rson);
	return;
}

void modify(int pre,int &now,int l,int r,int pos) {
	now=++tot;
	t[now]=t[pre],t[now].sum++;
	if(l==r) return;
	int mid=l+r>>1;
	if(pos<=mid) modify(t[pre].ch[0],lson,pos);
	else modify(t[pre].ch[1],rson,pos);
	return;
}

int query(int pre,int now,int l,int r,int k) {
	if(l==r) return l;
	int cnt=t[lc].sum-t[t[pre].ch[0]].sum,mid=l+r>>1;
	if(cnt>=k) return query(t[pre].ch[0],lson,k);
	else return query(t[pre].ch[1],rson,k-cnt);
}

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1,x;i<=n;i++)
		input(x),a[i]=Data(x,i);
	sort(a+1,a+n+1);
	int rank=1;
	b[a[1].id]=rank,c[1]=a[1].x;
	for(int i=2;i<=n;i++) {
		if(a[i].x!=a[i-1].x) rank++;
		b[a[i].id]=rank;
		c[rank]=a[i].x;
	}
	build(root[0],1,rank);
	for(int i=1;i<=n;i++)
		modify(root[i-1],root[i],1,rank,b[i]);
	for(int l,r,k;m;m--) {
		input(l),input(r),input(k);
		printf("%d\n",c[query(root[l-1],root[r],1,rank,k)]);
	}
	return 0;
}
