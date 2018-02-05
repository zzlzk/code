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

#define MAXN 81010
#define MAXM 300010

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
int pre[MAXN],path[MAXN];
int dis[MAXN];
bool inq[MAXN];
int src,decc;

#define inf 2147483647

bool spfa() {
	for(int i=src;i<=decc;i++)
		dis[i]=inf,pre[i]=-1;
	q.push(src),dis[src]=0,inq[src]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop(),inq[u]=false;
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].w) {
				dis[v]=dis[pre[v]=u]+edge[path[v]=i].w;
				if(!inq[v]) {
					q.push(v);
					inq[v]=true;
				}
			}
		}
	}
	return dis[decc]!=inf;
}

int n,m,sum;
int T[45][110],p[45];

int mcmf() {
	int cost=0;
	while(spfa()) {
		int flow=inf,x,y;
		for(int i=decc;i!=src;i=pre[i])
			flow=min(flow,edge[path[i]].cap);
		cost+=flow*dis[decc];
		for(int i=decc;i!=src;i=pre[i]) {
			edge[path[i]].cap-=flow,
			edge[path[i]^1].cap+=flow;
		}
		x=pre[decc],y=(x-n)%sum+1,x=(x-n-1)/sum+1;
		if(y<=sum) {
			for(int i=1;i<=n;i++)
				addedge(i,n+(x-1)*sum+y,1,y*T[i][x]);
			addedge(n+(x-1)*sum+y,decc,1,0);
		}
	}
	return cost;
}

int main() {
	input(n),input(m);
	for(int i=1,p;i<=n;i++) {
		input(p),sum+=p,
		addedge(src,i,p,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			input(T[i][j]);
	src=0,decc=n+sum*m+1;
	for(int i=1;i<=m;i++)
		addedge(n+(i-1)*sum+1,decc,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			addedge(i,n+(j-1)*sum+1,1,T[i][j]);
	printf("%d\n",mcmf());
	return 0;
}
