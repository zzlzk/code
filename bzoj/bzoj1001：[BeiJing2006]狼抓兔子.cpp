#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 1000000
#define maxm 3000010
#define inf 0x7fffffff
struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
}edge[maxm<<1];
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
	edge[++cnt]=Edge(v,u,cap,head[v]);
	head[v]=cnt;
	return;
}
inline bool bfs() {
	memset(agt,0,sizeof(agt));
	q.push(S);
	agt[S]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next)
			if(edge[i].cap&&!agt[edge[i].v]) {
				agt[edge[i].v]=agt[u]+1;
				q.push(edge[i].v);
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
	while(bfs()) ans+=dfs(S,inf);
	return ans;
}
int main() {
	int n=input(),m=input(),x;
	S=1,T=n*m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) {
			x=input();
			addedge(m*(i-1)+j,m*(i-1)+j+1,x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) {
			x=input();
			addedge(m*(i-1)+j,m*i+j,x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++) {
			x=input();
			addedge(m*(i-1)+j,m*i+j+1,x);
		}
	printf("%d",dinic());
	return 0;
}
