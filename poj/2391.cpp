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

#define MAXN 210
#define MAXM 170010
#define oo 9223372036854775807
#define inf 2147483647

struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN<<1],cnt=1;

void addedge(int u,int v,int cap) {
	edge[++cnt]=Edge(u,v,cap,head[u]),head[u]=cnt,
	edge[++cnt]=Edge(v,u,0,head[v]),head[v]=cnt;
	return;
}

queue<int> q;
int lev[MAXN<<1],cur[MAXN<<1];
int src,decc,n,m;

bool bfs() {
    for(int i=0;i<=decc;i++) lev[i]=-1;
    while(!q.empty()) q.pop();
    q.push(src),lev[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(lev[v]==-1&&edge[i].cap>0) {
                lev[v]=lev[u]+1;
                q.push(v);
                if(v==decc) return true;
            }
        }
    }
    return false;
}

int dfs(int u,int flow) {
    if(u==decc) return flow;
    int x,used=0;
    for(int &i=cur[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(lev[v]==lev[u]+1&&edge[i].cap>0) {
            x=dfs(v,min(edge[i].cap,flow-used));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(used==flow) break;
        }
    }
    if(used!=flow) lev[u]=-1;
    return used;
}

int dinic() {
    int ans=0;
    while(bfs()) {
        for(int i=0;i<=decc;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int cow[MAXN],cap[MAXN];
ll G[MAXN][MAXN];

void build(ll mid) {
	memset(head,0,sizeof(head));
	cnt=1;
	for(int i=1;i<=n;i++) {
		addedge(src,i,cow[i]),
		addedge(i+n,decc,cap[i]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]<=mid) addedge(i,j+n,inf);
	return;
}

int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		src=n<<1|1,decc=n+1<<1;
		int sum=0;
		for(int i=1;i<=n;i++)
			input(cow[i]),input(cap[i]),sum+=cow[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=(i==j?0:oo);
		for(int i=1,u,v;i<=m;i++) {
			ll w;
			input(u),input(v),input(w);
			G[u][v]=G[v][u]=min(G[u][v],w);
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(G[i][k]<oo&&G[k][j]<oo)
						G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
		ll ans=-1,l=0,r=0,mid;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(G[i][j]<oo) r=max(r,G[i][j]);
		while(l<=r) {
			build(mid=l+r>>1);
			if(dinic()==sum) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}