#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 55010
#define maxm 310010
#define inf 0x7fffffff
struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
}edge[maxm];
int head[maxn],agt[maxn];
int cnt=1,S,T;
queue<int>q;
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void addedge(int u,int v,int cap) {
	edge[++cnt]=Edge(u,v,cap,head[u]);
	head[u]=cnt;
	edge[++cnt]=Edge(v,u,0,head[v]);
	head[v]=cnt;
	return;
}
inline bool bfs() {
	memset(agt,0,sizeof(agt));
	q.push(0);
	agt[0]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next)
			if(edge[i].cap&&!agt[edge[i].v]) {
				q.push(edge[i].v);
				agt[edge[i].v]=agt[u]+1;
			}
	}
	return agt[T];
}
int dfs(int x,int maxflow) {
	if(x==T||!maxflow) return maxflow;
	int used=0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].cap&&agt[edge[i].v]==agt[x]+1) {
			int flow=dfs(edge[i].v,min(maxflow,edge[i].cap));
			used+=flow;
			maxflow-=flow;
			edge[i].cap-=flow;
			edge[i^1].cap+=flow;
		}
	if(!used) agt[x]=0;
	return used;
}
int dinic() {
	int ans=0;
	while(bfs()) ans+=dfs(0,inf);
	return ans;
}
int main() {
	int n=input(),m=input(),ans=0;
	T=n+m+1;
	for(int i=1,x;i<=n;i++) {
		x=input();
		addedge(i+m,T,x);
	}
	for(int i=1,x,y,z;i<=m;i++) {
		x=input(),y=input(),z=input();
		addedge(i,x+m,inf);
		addedge(i,y+m,inf);
		addedge(0,i,z);
		ans+=z;
	}
	printf("%d",ans-dinic());
	return 0;
}
