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

#define MAXN 20010
#define MAXM 200010
#define MAXK 25
#define MAXS (1<<21)+10

struct Edge {
	int u,v,w,next;
	Edge(int u=0,int v=0,int w=0,int next=0):
		u(u),v(v),w(w),next(next) {}
};

int n,m,k;
Edge edge[MAXM<<1];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
	edge[++cnt]=Edge(u,v,w,head[u]),
	head[u]=cnt;
	return;
}

#define inf 2147483647

queue<int> q;
int dis[MAXN];
bool inq[MAXN];

int f[MAXK][MAXS],g[MAXK][MAXN],r[MAXK],h[MAXK];

int spfa(int s) {
	for(int i=0;i<=n;i++)
		dis[i]=inf,inq[i]=false;
	q.push(s),dis[s]=0,inq[s]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop(),inq[u]=false;
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			if(dis[v]>dis[u]+edge[i].w) {
				dis[v]=dis[u]+edge[i].w;
				if(!inq[v]) {
					q.push(v);
					inq[v]=true;
				}
			}
		}
	}
	if(s==1) return dis[n];
	for(int i=1;i<=k;i++) g[s-1][i]=dis[i+1];
	if(!r[s-1]) f[s-1][1<<s-2]=dis[1];
	h[s-1]=dis[n];
	return 1;
}

int main() {
	input(n),input(m),input(k);
	for(int i=1,u,v,w;i<=m;i++) {
		input(u),input(v),input(w),
		addedge(u,v,w),addedge(v,u,w);
	}
	int gg;
	for(input(gg);gg;gg--) {
		int ri,si;
		input(ri),input(si);
		r[si-1]|=1<<ri-2;
	}
	if(!k) {
		printf("%d\n",spfa(1));
		return 0;
	}
	for(int i=0;i<=k;i++)
		for(int s=0;s<1<<k;s++)
			f[i][s]=inf/3;
	for(int i=2;i<=k+1;i+=spfa(i));
	for(int s=1;s<1<<k;s++)
		for(int i=1;i<=k;i++)
			if(s&(1<<i-1))
				for(int j=1;j<=k;j++)
					if(!(s&(1<<j-1))&&(s&r[j])==r[j])
						f[j][s|(1<<j-1)]=min(f[j][s|(1<<j-1)],f[i][s]+g[i][j]);
	int ans=inf;
	for(int i=1;i<=k;i++)
		ans=min(ans,f[i][(1<<k)-1]+h[i]);
	printf("%d\n",ans);
	return 0;
}
