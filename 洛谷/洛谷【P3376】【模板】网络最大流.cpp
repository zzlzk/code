#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 10010
#define maxm 100010
#define inf 0x7fffffff
struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
}edge[maxm<<1];
int head[maxn],cnt=1,agt[maxn],s,t,n,m;
inline int input() {
	char c=getchar();int x=0,a=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0'; 
	return x*a;
}
void addedge(int u,int v,int cap) {
	edge[++cnt]=Edge(u,v,cap,head[u]);
	head[u]=cnt;
	edge[++cnt]=Edge(v,u,0,head[v]);
	head[v]=cnt;
	return;
}
inline bool bfs() {
	memset(agt,0,sizeof(agt));
	queue<int>q;
	q.push(s);
	agt[s]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next)
			if(edge[i].cap&&!agt[edge[i].v]) {
				agt[edge[i].v]=agt[u]+1;
				q.push(edge[i].v);
			}
	}
	return agt[t];
}
int dfs(int x,int maxflow) {
	if(!maxflow||x==t) return maxflow;
	int used=0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].cap&&agt[edge[i].v]==agt[x]+1) {
			int flow=dfs(edge[i].v,min(maxflow,edge[i].cap));
			used+=flow;
			maxflow-=flow;
			edge[i].cap-=flow;
			edge[i^1].cap+=flow;
		}
	if(!used) agt[x]=0;//据说加上这一句永远不会TLE
	return used;
}
inline int dinic() {
	int ans=0;
	while(bfs()) ans+=dfs(s,inf);
	return ans;
}
int main() {
	n=input();m=input();s=input();t=input();
	for(int i=1;i<=m;i++) {
		int u=input(),v=input(),cap=input();
		addedge(u,v,cap);
	}
	printf("%d",dinic());
	return 0;
}
