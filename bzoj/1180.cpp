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

#define MAXN 30010

int fa[MAXN],ch[MAXN][2];
int val[MAXN],sum[MAXN];
int st[MAXN],top;
bool rev[MAXN];

bool isroot(int x) {
	return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
}

#define lc ch[x][0]
#define rc ch[x][1]

void updata(int x) {
	sum[x]=sum[lc]+sum[rc]+val[x];
	return;
}

void pushdown(int x) {
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

void cut(int x,int y) {
	split(x,y);
	ch[y][0]=fa[ch[y][0]]=0;
	return updata(y);
}

int query(int x,int y) {
	split(x,y);
	return sum[y];
}

void modify(int x,int y) {
	access(x),splay(x),val[x]=y;
	return updata(x);
}

int find(int x) {
	access(x),splay(x);
	while(lc) x=lc;
	return x;
}

int main() {
	int n,q;
	input(n);
	for(int i=1;i<=n;i++)
		input(val[i]),sum[i]=val[i];
	input(q);
	char op[15];
	for(int x,y;q;q--) {
		scanf("%s",op),
		input(x),input(y);
		if(op[0]=='b') {
			if(find(x)==find(y)) puts("no");
			else link(x,y),puts("yes");
		} else if(op[0]=='p') modify(x,y);
		else if(op[0]=='e') {
			if(find(x)!=find(y)) puts("impossible");
			else printf("%d\n",query(x,y));
		}
	}
	return 0;
}
