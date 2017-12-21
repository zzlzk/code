#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned int uint;

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

#define MAXN 100010
#define mod 51061

int fa[MAXN],ch[MAXN][2],size[MAXN];
int st[MAXN],top;
uint sum[MAXN],mul[MAXN],plus[MAXN],v[MAXN];
bool rev[MAXN];

bool isroot(int x) {
	return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
}

#define lc ch[x][0]
#define rc ch[x][1]

void updata(int x) {
	sum[x]=(sum[lc]+sum[rc]+v[x])%mod;
	size[x]=(size[lc]+size[rc]+1)%mod;
	return;
}

void calc(int x,int m,int p) {
	if(!x) return;
	v[x]=(v[x]*m+p)%mod,
	sum[x]=(sum[x]*m+p*size[x])%mod,
	mul[x]=(mul[x]*m)%mod,
	plus[x]=(plus[x]*m+p)%mod;
	return;
}

void pushdown(int x) {
	if(rev[x]) {
		rev[x]=0,rev[lc]^=1,rev[rc]^=1,
		swap(lc,rc);
	}
	if(mul[x]!=1||plus[x]) {
		calc(lc,mul[x],plus[x]),
		calc(rc,mul[x],plus[x]);
	}
	mul[x]=1,plus[x]=0;
	return;
}

void rotate(int x) {
	int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
	if(!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z,
	ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y,
	ch[x][d]=y,fa[y]=x,
	updata(y),updata(x);
	return;
}

void splay(int x) {
	st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])
		st[++top]=fa[i];
	while(top) pushdown(st[top--]);
	while(!isroot(x)) {
		int y=fa[x],z=fa[y];
		if(!isroot(y)) {
			if(ch[y][1]==x^ch[z][1]==y) rotate(x);
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

void cut(int x,int y) {
	split(x,y),
	ch[y][0]=fa[ch[y][0]]=0;
	return updata(y);
}

int query(int x,int y) {
	split(x,y);
	return sum[y]%mod;
}

void modify_mul(int x,int y,uint z) {
	split(x,y);
	return calc(y,z,0);
}

void modify_plus(int x,int y,uint z) {
	split(x,y);
	return calc(y,1,z);
}

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1;i<=n;i++)
		mul[i]=v[i]=sum[i]=size[i]=1;
	for(int i=1,u,v;i<n;i++) {
		input(u),input(v),
		link(u,v);
	}
	char op[5];
	for(int x,y,z,xx,yy;m;m--) {
		scanf("%s",op);
		if(op[0]=='+') {
			input(x),input(y),input(z),
			modify_plus(x,y,z);
		} else if(op[0]=='-') {
			input(x),input(y),input(xx),input(yy),
			cut(x,y),link(xx,yy);
		} else if(op[0]=='*') {
			input(x),input(y),input(z);
			modify_mul(x,y,z);
		} else if(op[0]=='/') {
			input(x),input(y),
			printf("%d\n",query(x,y));
		}
	}
	return 0;
}
