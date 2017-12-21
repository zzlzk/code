#include<map>
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

#define MAXN 8010
#define MAXC 105

int st[MAXN],top;

struct Link_Cut_Tree {
	int fa[MAXN],ch[MAXN][2];
	bool rev[MAXN];

	bool isroot(int x) {
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}

#define lc ch[x][0]
#define rc ch[x][1]

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
				if(ch[z][1]==y^ch[y][1]==x) rotate(x);
				else rotate(y);
			}
			rotate(x);
		}
		return;
	}

	void access(int x) {
		for(int t=0;x;x=fa[t=x])
			splay(x),ch[x][1]=t;
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
		return;
	}

	int find(int x) {
		access(x),splay(x);
		while(lc) x=lc;
		return x;
	}

#undef lc
#undef rc

};

Link_Cut_Tree LCT[MAXC];

int cnt[MAXN][MAXC];

struct Edge {
	int u,v;
	Edge(int u=0,int v=0):
		u(u),v(v) {}
	bool operator < (const Edge &q) const {
		if(u!=q.u) return u<q.u;
		return v<q.v;
	}
};

map<Edge,int> company;

int main() {
	int n,m,c,T;
	input(n),input(m),input(c),input(T);
	for(int x,y,z;m;m--) {
		input(x),input(y),input(z);
		LCT[z].link(x,y);
		company[Edge(x,y)]=z,company[Edge(y,x)]=z,
		cnt[x][z]++,cnt[y][z]++;
	}
	for(int x,y,z;T;T--) {
		input(x),input(y),input(z);
		int com=company[Edge(x,y)];
		if(!com) puts("No such cable.");
		else if(com==z) puts("Already owned.");
		else if(cnt[x][z]>1||cnt[y][z]>1)
			puts("Forbidden: monopoly.");
		else if(LCT[z].find(x)==LCT[z].find(y))
			puts("Forbidden: redundant.");
		else {
			puts("Sold."),
			cnt[x][com]--,cnt[x][z]++,
			cnt[y][com]--,cnt[y][z]++,
			LCT[com].cut(x,y),LCT[z].link(x,y),
			company[Edge(x,y)]=z,company[Edge(y,x)]=z;
		}
	}
	return 0;
}
