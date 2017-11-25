#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
#define maxn 100010
#define mod 20130426ll
int ch[maxn][2],fa[maxn];
int size[maxn],n,root;
ll a[maxn],add[maxn];
ll mul[maxn],mi,ans;
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void updata(int x) {
	int lc=ch[x][0],rc=ch[x][1];
	size[x]=size[lc]+size[rc]+1;
	return;
}
inline void pushdown(int x) {
	int lc=ch[x][0],rc=ch[x][1];
	ll &Mul=mul[x],&Add=add[x];
	a[x]=(a[x]*Mul)%mod;
	a[x]=(a[x]+Add)%mod;
	add[lc]=(add[lc]*Mul+Add)%mod;
	add[rc]=(add[rc]*Mul+Add)%mod;
	mul[lc]=(mul[lc]*Mul)%mod;
	mul[rc]=(mul[rc]*Mul)%mod;
	Mul=1ll,Add=0ll;
	return;
}
inline int son(int x) {
	return ch[fa[x]][1]==x;
}
void rotate(int x) {
	int y=fa[x],z=fa[y];
	int b=son(x),c=son(y),a=ch[x][!b];
	if(z) ch[z][c]=x;
	else root=x;
	fa[x]=z;
	if(a) fa[a]=y;
	ch[y][b]=a;
	ch[x][!b]=y;
	fa[y]=x;
	updata(y);
	updata(x);
	return;
}
void splay(int x,int i) {
	while(fa[x]!=i) {
		int y=fa[x],z=fa[y];
		if(z==i) {
			pushdown(y);
			pushdown(x);
			rotate(x);
		} else {
			pushdown(z);
			pushdown(y);
			pushdown(x);
			if(son(x)==son(y)) {
				rotate(y);
				rotate(x);
			} else {
				rotate(x);
				rotate(x);
			}
		}
	}
	return;
}
int getkth(int x,int k) {
	int lc=ch[x][0];
	if(size[lc]+1==k) return x;
	if(size[lc]>=k) return getkth(lc,k);
	return getkth(ch[x][1],k-size[lc]-1);
}
void plus(int L,int R,int v) {
	int l=getkth(root,L);
	int r=getkth(root,R+2);
	splay(l,0);
	splay(r,l);
	int x=ch[r][0];
	add[x]=(add[x]+v)%mod;
	return;
}
void multiply(int L,int R,int v) {
	int l=getkth(root,L);
	int r=getkth(root,R+2);
	splay(l,0);
	splay(r,l);
	int x=ch[r][0];
	add[x]=(add[x]*v)%mod;
	mul[x]=(mul[x]*v)%mod;
	return;
}
void multiply_plus(int L,int R) {
	int rm=getkth(root,R);
	int r1=getkth(root,R+1);
	int r2=getkth(root,R+2);
	splay(rm,0);
	splay(r2,rm);
	pushdown(rm);
	pushdown(r2);
	pushdown(r1);
	a[r2]=(a[r2]+a[r1])%mod;
	ch[r2][0]=0;
	size[r2]--;
	size[rm]--;
	int lm=getkth(root,L);
	int l=getkth(root,L+1);
	splay(lm,0);
	splay(l,lm);
	pushdown(lm);
	pushdown(l);
	ch[l][0]=r1;
	fa[r1]=l;
	size[r1]=1;
	size[l]++;
	size[lm]++;
	a[r1]=0;
	add[r1]=0;
	mul[r1]=1;
	return;
}
void dfs(int x,ll v) {
	pushdown(x);
	int lc=ch[x][0],rc=ch[x][1];
	if(lc) dfs(lc,v);
	if(mi==-1) mi=1;
	else {
		ans=(ans+a[x]*mi)%mod;
		mi=(mi*v)%mod;
	}
	if(rc) dfs(rc,v);
	return;
}
void query(ll v) {
	ans=0,mi=-1;
	dfs(root,v);
	printf("%lld\n",ans);
	return;
}
void init(int n) {
	n+=5;
	root=1;
	for(int i=1;i<n;i++) ch[i][1]=i+1;
	for(int i=2;i<=n;i++) fa[i]=i-1;
	for(int i=n;i>=1;i--) {
		updata(i);
		mul[i]=1ll;
	}
	return;
}
int main() {
	n=input();
	for(init(n);n>=1;n--) {
		char op[10];
		scanf("%s",op);
		int x=input(),len=strlen(op);
		if(op[0]=='m') {
			int y=input();
			if(len==3) {
				int z=input();
				multiply(x+1,y+1,z);
			} else multiply_plus(x+1,y+1);
		} else if(op[0]=='a') {
			int y=input(),z=input();
			plus(x+1,y+1,z);
		} else query((ll)x);
	}
	return 0;
}
