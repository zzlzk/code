#include<queue>
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

#define MAXN 410
#define MAXM 10310

struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap) {
	edge[++cnt]=Edge(u,v,cap,head[u]),head[u]=cnt,
	edge[++cnt]=Edge(v,u,0,head[v]),head[v]=cnt;
	return;
}

queue<int> q;
int lev[MAXN],cur[MAXN];
int src,decc;

bool bfs() {
	for(int i=src;i<=decc;i++)
		lev[i]=-1;
	while(!q.empty()) q.pop();
	q.push(src),lev[src]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			if(lev[v]==-1&&edge[i].cap>0) {
				lev[v]=lev[u]+1;
				if(v==decc) return true;
				q.push(v);
			}
		} 
	}
	return false;
}

int dfs(int u,int flow) {
	if(u==decc) return flow;
	int used=0,x;
	for(int &i=cur[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(lev[v]==lev[u]+1&&edge[i].cap>0) {
			x=dfs(v,min(flow-used,edge[i].cap)),
			used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
			if(used==flow) break;
		}
	}
	if(flow!=used) lev[u]=-1;
	return used;
}

#define inf 2147483647

int dinic() {
	int ans=0;
	while(bfs()) {
		for(int i=src;i<=decc;i++)
			cur[i]=head[i];
		ans+=dfs(src,inf);
	}
	return ans;
}

int main() {
	int N,F,D;
	while(scanf("%d%d%d",&N,&F,&D)!=EOF) {
		cnt=1,src=0,decc=F+2*N+D+1,
		memset(head,0,sizeof(head));
		for(int i=1;i<=F;i++) addedge(src,i,1);
		for(int i=1;i<=D;i++) addedge(F+2*N+i,decc,1);
		for(int i=1;i<=N;i++) addedge(F+i,F+N+i,1);
		for(int i=1,T1,T2,x;i<=N;i++) {
			input(T1),input(T2);
			while(T1--) input(x),addedge(x,F+i,1);
			while(T2--) input(x),addedge(F+N+i,F+2*N+x,1);
		}
		printf("%d\n",dinic());
	}
	return 0;
}