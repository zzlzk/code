#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1000010
#define inf 1000000000
int n,m,rt,cnt;
int a[maxn],id[maxn],fa[maxn],c[maxn][2];
int sum[maxn],size[maxn],v[maxn],mx[maxn],lx[maxn],rx[maxn];
bool tag[maxn],rev[maxn];
queue<int>q;
inline int input() {
	char c=getchar();int x=0,a=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
void updata(int x) {
	int l=c[x][0],r=c[x][1];
	sum[x]=sum[l]+sum[r]+v[x];
	size[x]=size[l]+size[r]+1;
	mx[x]=max(mx[l],mx[r]);
	mx[x]=max(mx[x],rx[l]+v[x]+lx[r]);
	lx[x]=max(lx[l],sum[l]+v[x]+lx[r]);
	rx[x]=max(rx[r],sum[r]+v[x]+rx[l]);
	return;
}
void pushdown(int x) {
	int l=c[x][0],r=c[x][1];
	if(tag[x]) {
		rev[x]=tag[x]=false;
		if(l) tag[l]=true,v[l]=v[x],sum[l]=v[x]*size[l];
		if(r) tag[r]=true,v[r]=v[x],sum[r]=v[x]*size[r];
		if(v[x]>=0) {
			if(l) lx[l]=rx[l]=mx[l]=sum[l];
			if(r) lx[r]=rx[r]=mx[r]=sum[r];
		} else {
			if(l) lx[l]=rx[l]=0,mx[l]=v[x];
			if(r) lx[r]=rx[r]=0,mx[r]=v[x];
		}
	}
	if(rev[x]) {
		rev[x]^=1;rev[l]^=1;rev[r]^=1;
		swap(lx[l],rx[l]),swap(lx[r],rx[r]);
		swap(c[l][0],c[l][1]),swap(c[r][0],c[r][1]);
	}
	return;
}
void rotate(int x,int &k) {
	int y=fa[x],z=fa[y];
	int l=(c[y][1]==x),r=l^1;
	if(y==k) k=x;
	else c[z][c[z][1]==y]=x;
	fa[c[x][r]]=y;
	fa[y]=x;
	fa[x]=z;
	c[y][l]=c[x][r];
	c[x][r]=y;
	updata(y);
	updata(x);
	return;
}
void splay(int x,int &k) {
	while(x!=k) {
		int y=fa[x],z=fa[y];
		if(y!=k) {
			if(c[y][0]==x^c[z][0]==y) rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
	return;
}
int find(int x,int rk) {
	pushdown(x);
	int l=c[x][0],r=c[x][1];
	if(size[l]+1==rk) return x;
	if(size[l]>=rk) return find(l,rk);
	return find(r,rk-size[l]-1);
}
void rec(int x) {
	if(!x) return;
	int l=c[x][0],r=c[x][1];
	rec(l);
	rec(r);
	q.push(x);
	fa[x]=c[x][0]=c[x][1]=0;
	tag[x]=rev[x]=false;
	return;
}
int split(int k,int tot) {
	int x=find(rt,k),y=find(rt,k+tot+1);
	splay(x,rt);
	splay(y,c[x][1]);
	return c[y][0];
}
void query(int k,int tot) {
	int x=split(k,tot);
	printf("%d\n",sum[x]);
	return;
}
void modify(int k,int tot,int val) {
	int x=split(k,tot),y=fa[x];
	v[x]=val;
	tag[x]=true;
	sum[x]=size[x]*val;
	if(val>=0) lx[x]=rx[x]=mx[x]=sum[x];
	else lx[x]=rx[x]=0,mx[x]=val;
	updata(y);
	updata(fa[y]);
	return;
}
void rever(int k,int tot) {
	int x=split(k,tot),y=fa[x];
	if(!tag[x]) {
		rev[x]^=1;
		swap(c[x][0],c[x][1]);
		swap(lx[x],rx[x]);
		updata(y);
		updata(fa[y]);
	}
	return;
}
void erase(int k,int tot) {
	int x=split(k,tot),y=fa[x];
	rec(x);
	c[y][0]=0;
	updata(y);
	updata(fa[y]);
	return;
}
void build(int l,int r,int f) {
	if(l>r) return;
	int mid=(l+r)>>1,now=id[mid],last=id[f];
	if(l==r) {
		sum[now]=a[l];
		size[now]=1;
		tag[now]=rev[now]=false;
		if(a[l]>=0) lx[now]=rx[now]=mx[now]=a[l];
		else lx[now]=rx[now]=0,mx[now]=a[l];
	} else build(l,mid-1,mid),build(mid+1,r,mid);
	v[now]=a[mid];
	fa[now]=last;
	updata(now);
	c[last][mid>=f]=now;
	return;
}
void insert(int k,int tot) {
	for(int i=1;i<=tot;i++) a[i]=input();
	for(int i=1;i<=tot;i++)
		if(!q.empty()) id[i]=q.front(),q.pop();
		else id[i]=++cnt;
	build(1,tot,0);
	int z=id[1+tot>>1];
	int x=find(rt,k+1),y=find(rt,k+2);
	splay(x,rt);
	splay(y,c[x][1]);
	fa[z]=y;
	c[y][0]=z;
	updata(y);
	updata(x);
	return;
}
int main() {
	n=input(),m=input();
	mx[0]=a[1]=a[n+2]=-inf;
	for(int i=1;i<=n;i++) a[i+1]=input();
	for(int i=1;i<=n+2;i++) id[i]=i;
	build(1,n+2,0);
	rt=(n+3)>>1;
	cnt=n+2;
	while(m--) {
		int k,tot,val;
		char ch[10];
		scanf("%s",ch);
		if(ch[0]!='M'||ch[2]!='X') k=input(),tot=input();
		if(ch[0]=='I') insert(k,tot);
		if(ch[0]=='D') erase(k,tot);
		if(ch[0]=='M') {
			if(ch[2]=='X') printf("%d\n",mx[rt]);
			else val=input(),modify(k,tot,val);
		}
		if(ch[0]=='R') rever(k,tot);
		if(ch[0]=='G') query(k,tot);
	}
	return 0;
}
