#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef queue<int> Queue;
#define maxn 110
#define inf 0x7fffffff
struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
}edge[maxn*maxn];
int head[maxn],agt[maxn];
int cnt=1,S,T;
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
inline void clear() {
	memset(agt,0,sizeof(agt));
	return;
}
inline bool bfs() {
	clear();
	Queue q;
	q.push(S);
	agt[S]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next)
			if(!agt[edge[i].v]&&edge[i].cap) {
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
			int flow=dfs(edge[i].v,min(edge[i].cap,maxflow));
			used+=flow;
			maxflow-=flow;
			edge[i].cap-=flow;
			edge[i^1].cap+=flow;
		}
	return used;
}
int dinic() {
	int ans=0;
	while(bfs()) ans+=dfs(S,inf);
	return ans;
}
int main() {
	int m=input(),n=input(),a,b;
	while(scanf("%d%d",&a,&b))
		if(a==-1&&b==-1) break;
		else addedge(a,b,inf);
	S=0,T=n+1;
	for(int i=1;i<=m;i++) addedge(0,i,1);
	for(int i=m+1;i<=n;i++) addedge(i,T,1);
	a=dinic();
	if(!a) {
		printf("No Solution!\n");
		return 0;
	} else printf("%d\n",a);
	for(int i=2;i<=cnt;i+=2) {
		if(edge[i].u==S||edge[i].v==S) continue;
		if(edge[i].u==T||edge[i].v==T) continue;
		if(edge[i^1].cap==0) continue;
		printf("%d %d\n",edge[i].u,edge[i].v);
	}
	return 0;
}
