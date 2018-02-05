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

#define MAXN 1010
#define MAXM 37010

struct Edge {
	int u,v,cap,w,next;
	Edge(int u=0,int v=0,int cap=0,int w=0,int next=0):
		u(u),v(v),cap(cap),w(w),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap,int w) {
	edge[++cnt]=Edge(u,v,cap,w,head[u]),head[u]=cnt,
	edge[++cnt]=Edge(v,u,0,-w,head[v]),head[v]=cnt;
	return;
}

queue<int> q;
int pre[MAXN],dis[MAXN];
bool inq[MAXN];
int src,decc;

#define inf 2147483647

bool spfa() {
	for(int i=src;i<=decc;i++)
		dis[i]=inf;
	q.push(src),dis[src]=0,inq[src]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop(),inq[u]=false;
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].w) {
				dis[v]=dis[u]+edge[pre[v]=i].w;
				if(!inq[v]) {
					q.push(v);
					inq[v]=true;
				}
			}
		}
	}
	return dis[decc]!=inf;
}

int mcmf() {
	int cost=0;
	while(spfa()) {
		int flow=inf;
		for(int i=pre[decc];i;i=pre[edge[i].u])
			flow=min(flow,edge[i].cap);
		for(int i=pre[decc];i;i=pre[edge[i].u]) {
			cost+=flow*edge[i].w,
			edge[i].cap-=flow,edge[i^1].cap+=flow;
		}
	}
	return cost;
}

int T[65][15];

int main() {
	int n,m;
	input(m),input(n),
	src=0,decc=n*m+n+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			input(T[i][j]);
	for(int i=1;i<=n*m;i++)
		addedge(src,i,1,0);
	for(int i=n*m+1;i<=n*m+n;i++)
		addedge(i,decc,1,0);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				addedge((i-1)*n+j,n*m+k,1,T[k][i]*j);
	printf("%.2lf\n",1.00*mcmf()/n);
	return 0;
}
