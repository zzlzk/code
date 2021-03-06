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

int fa[MAXN],ch[MAXN][2],st[MAXN],top;
bool rev[MAXN];

bool isroot(int x) {
	return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}

#define lc ch[k][0]
#define rc ch[k][1]

void pushdown(int k) {
	if(rev[k]) {
		rev[lc]^=1,rev[rc]^=1,
		swap(lc,rc),
		rev[k]=0;
	}
	return;
}

void rotate(int x) {
	int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
	if(!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z;
	ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y;
	ch[x][d]=y,fa[y]=x;
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
			if(ch[y][0]==x^ch[z][0]==y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	return;
}

void access(int x) {
	for(int t=0;x;x=fa[x]) {
		splay(x),
		ch[x][1]=t,
		t=x;
	}
	return;
}

void makeroot(int x) {
	access(x),
	splay(x),
	rev[x]^=1;
	return;
}

void link(int x,int y) {
	makeroot(x),
	fa[x]=y;
	return splay(x);
}

void split(int x,int y) {
	makeroot(x),access(y);
	return splay(y);
}

void cut(int x,int y) {
	split(x,y),
	ch[y][0]=fa[x]=0;
	return;
}

int Find(int x) {
	access(x),splay(x);
	for(;ch[x][0];x=ch[x][0]);
	return x;
}

int main() {
	int n,m;
	input(n),input(m);
	char op[10];
	for(int x,y;m;m--) {
		scanf("%s",op),
		input(x),input(y);
		if(op[0]=='C') link(x,y);
		else if(op[0]=='D') cut(x,y);
		else puts(Find(x)==Find(y)?"Yes":"No");
	}
	return 0;
}
