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

#define MAXN 40010

int n,m;
int id[MAXN];
int fa[MAXN],ch[MAXN][2],st[MAXN],top;
int sum[MAXN],Max[MAXN],Min[MAXN],v[MAXN];
bool rev[MAXN],unm[MAXN];

bool isroot(int x) {
	return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}

#define lc ch[x][0]
#define rc ch[x][1]

void updata(int x) {
	sum[x]=sum[lc]+sum[rc]+v[x],
	Min[x]=min(Min[lc],Min[rc]),
	Max[x]=max(Max[lc],Max[rc]);
	if(x>n) {
		Min[x]=min(Min[x],v[x]),
		Max[x]=max(Max[x],v[x]);
	}
	return;
}

void UNM(int x) {
	unm[x]^=1,
	sum[x]=-sum[x],v[x]=-v[x],
	swap(Max[x],Min[x]),
	Max[x]=-Max[x],Min[x]=-Min[x];
	return;
}

void pushdown(int x) {
	if(unm[x]) {
		unm[x]=0;
		if(lc) UNM(lc);
		if(rc) UNM(rc);
	}
	if(rev[x]) {
		rev[lc]^=1,rev[rc]^=1,rev[x]=0,
		swap(lc,rc);
	}
	return;
}

void rotate(int x) {
	int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
	if(!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z,
	ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y,
	ch[x][d]=y,fa[y]=x;
	return updata(y),updata(x);
}

void splay(int x) {
	st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])
		st[++top]=fa[i];
	while(top) pushdown(st[top--]);
	while(!isroot(x)) {
		int y=fa[x],z=fa[y];
		if(!isroot(y)) {
			if(ch[z][1]==y^ch[y][1]==x) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	return;
}

void access(int x) {
	for(int t=0;x;x=fa[t=x])
		splay(x),ch[x][1]=t,updata(x);
	return;
}

void makeroot(int x) {
	access(x),splay(x),rev[x]^=1;
	return;
}

void split(int x,int y) {
	makeroot(x),access(y);
	return splay(y);
}

void link(int x,int y) {
	makeroot(x),fa[x]=y;
	return splay(x);
}

void modify(int i,int w) {
	splay(i=id[i]),v[i]=w;
	return updata(i);
}

int query(int x,int y,int type) {
	split(x,y);
	return type==1?sum[y]:(type==2?Min[y]:Max[y]);
}

#define inf 2147483647

int main() {
	input(n);
	for(int i=0;i<=n;i++)
		Min[i]=inf,Max[i]=-inf;
	for(int i=1,tot=n,x,y,z;i<n;i++) {
		input(x),input(y),input(z),
		id[i]=++tot,
		link(++x,tot),link(++y,tot);
		v[tot]=Min[tot]=Max[tot]=sum[tot]=z;
	}
	input(m);
	char op[5];
	for(int i,w,x,y;m;m--) {
		scanf("%s",op);
		if(op[0]=='C') {
			input(i),input(w),
			modify(i,w);
		} else if(op[0]=='N') {
			input(x),input(y),
			split(++x,++y),UNM(y);
		} else if(op[0]=='S') {
			input(x),input(y),
			printf("%d\n",query(++x,++y,1));
		} else if(op[1]=='I') {
			input(x),input(y),
			printf("%d\n",query(++x,++y,2));
		} else if(op[1]=='A') {
			input(x),input(y),
			printf("%d\n",query(++x,++y,3));
		}
	}
	return 0;
}
