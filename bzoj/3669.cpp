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

#define MAXN 50010
#define MAXM 100010

int fa[MAXN+MAXM],ch[MAXN+MAXM][2];
int Max[MAXN+MAXM],val[MAXN+MAXM];
int st[MAXN+MAXM],top;
bool rev[MAXN+MAXM];

bool isroot(int x) {
	return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; 
}

#define lc ch[x][0]
#define rc ch[x][1]

void updata(int x) {
	Max[x]=x;
	if(val[Max[lc]]>val[Max[x]]) Max[x]=Max[lc];
	if(val[Max[rc]]>val[Max[x]]) Max[x]=Max[rc];
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
	return Max[y];
}

int f[MAXN];

int find(int x) {
	return f[x]==x?x:f[x]=find(f[x]);
}

struct Edge {
	int u,v,a,b;
	Edge(int u=0,int v=0,int a=0,int b=0):
		u(u),v(v),a(a),b(b) {}
	bool operator < (const Edge &q) const {
		return a<q.a;
	}
};

Edge edge[MAXM];

#define inf 2147483647

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1,u,v,a,b;i<=m;i++) {
		input(u),input(v),input(a),input(b);
		edge[i]=Edge(u,v,a,b);
	}
	sort(edge+1,edge+m+1);
	int ans=inf;
	for(int i=1,u,v,a,b;i<=m;i++) {
		u=edge[i].u,v=edge[i].v,
		a=edge[i].a,b=edge[i].b;
		int fu=find(u),fv=find(v);
		if(fu==fv) {
			int id=query(u,v);
			if(val[id]>b)
				cut(id,edge[id-n].u),cut(id,edge[id-n].v);
			else {
				if(find(1)==find(n))
					ans=min(ans,a+val[query(1,n)]);
				continue;
			}
		} else f[fu]=fv;
		val[n+i]=b,Max[n+i]=n+i,
		link(u,n+i),link(v,n+i);
		if(find(1)==find(n))
			ans=min(ans,a+val[query(1,n)]);
	}
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}
