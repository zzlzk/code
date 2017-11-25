#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 110
#define maxm 500010
#define inf 0x7fffffff
struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
}edge[maxm];
int head[maxm],agt[maxm];
int a[maxn][maxn],b[maxn][maxn];
int cnt=1,S,T,n,m,ans,sum;
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
inline void addedge0(int u,int v,int cap) {
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
		if(edge[i].cap&&agt[x]+1==agt[edge[i].v]) {
			int flow=dfs(edge[i].v,min(edge[i].cap,maxflow));
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
inline int d(int x,int y) {
	return (x-1)*m+y;
}
int main() {
	n=input(),m=input(),sum=ans=S=0,T=n*m+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			a[i][j]=input();
			sum+=a[i][j];
			a[i][j]<<=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			b[i][j]=input();
			sum+=b[i][j];
			b[i][j]<<=1;
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) {
			int x=input();
			a[i][j]+=x;
			a[i+1][j]+=x;
			sum+=x;
			addedge0(d(i,j),d(i+1,j),x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) {
			int x=input();
			b[i][j]+=x;
			b[i+1][j]+=x;
			sum+=x;
			addedge0(d(i,j),d(i+1,j),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) {
			int x=input();
			a[i][j]+=x;
			a[i][j+1]+=x;
			sum+=x;
			addedge0(d(i,j),d(i,j+1),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) {
			int x=input();
			b[i][j]+=x;
			b[i][j+1]+=x;
			sum+=x;
			addedge0(d(i,j),d(i,j+1),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			addedge(S,d(i,j),a[i][j]);
			addedge(d(i,j),T,b[i][j]);
		}
	printf("%d",sum-(dinic()>>1));
	return 0;
}
