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

struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
};

Edge edge[MAXN<<1];
int head[MAXN],cnt;

void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]);
	head[u]=cnt;
	return;
}

int n,m;
int fa[MAXN],c[MAXN];
int f[MAXN][2];

void dfs(int u) {
	if(u<=n) {
		f[u][c[u]]=0,f[u][c[u]^1]=1<<20;
		return;
	}
	for(int i=head[u],v;i;i=edge[i].next)
		if((v=edge[i].v)!=fa[u]) {
			fa[v]=u,dfs(v);
			f[u][0]+=min(f[v][0],f[v][1]+1),
			f[u][1]+=min(f[v][1],f[v][0]+1);
		}
	return;
}

int main() {
	input(m),input(n);
	for(int i=1;i<=n;i++) input(c[i]);
	for(int i=1,u,v;i<m;i++) {
		input(u),input(v),
		addedge(u,v),addedge(v,u);
	}
	dfs(m),
	printf("%d\n",min(f[m][0],f[m][1])+1);
	return 0;
}
