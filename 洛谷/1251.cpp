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

#define MAXN 4010
#define MAXM 24010

struct Edge {
    int u,v,cap,next;
    ll w;
    Edge(int u=0,int v=0,ll w=0,int cap=0,int next=0):
        u(u),v(v),w(w),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,ll w,int cap) {
    edge[++cnt]=Edge(u,v,w,cap,head[u]);
    head[u]=cnt;
    return;
}

queue<int> q;
ll dis[MAXN];
bool inq[MAXN];
int path[MAXN],pre[MAXN];
int n,src,decc;

#define inf 2147483647

bool spfa() {
    for(int i=1;i<=decc;i++)
        dis[i]=inf,pre[i]=-1,inq[i]=false;
    q.push(src),inq[src]=true,dis[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].w) {
                dis[v]=edge[path[v]=i].w+dis[pre[v]=u];
                if(!inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return pre[decc]!=-1;
}

ll flow,cost;

void mcmf() {
    while(spfa()) {
        int f=inf;
        for(int u=decc;u!=src;u=pre[u])
            f=min(f,edge[path[u]].cap);
        flow+=f,cost+=dis[decc]*f;
        for(int u=decc;u!=src;u=pre[u]) {
            edge[path[u]].cap-=f,
            edge[path[u]^1].cap+=f;
        }
    }
    return;
}

int r[2010];

int main() {
    int p,ftime,fcost,stime,scost;
    input(n),input(p),input(ftime),input(fcost),input(stime),input(scost);
    for(int i=1;i<=n;i++) input(r[i]);
    src=n<<1|1,decc=n+1<<1;
    for(int i=1;i<=n;i++) {
        addedge(src,i,0,r[i]),addedge(i,src,0,0),
        addedge(i+n,decc,0,r[i]),addedge(decc,i+n,0,0),
        addedge(src,i+n,p,inf),addedge(i+n,src,-p,0);
        if(i<n) addedge(i,i+1,0,inf),addedge(i+1,i,0,0);
        if(i+ftime<=n) addedge(i,i+n+ftime,fcost,inf),addedge(i+n+ftime,i,-fcost,0);
        if(i+stime<=n) addedge(i,i+n+stime,scost,inf),addedge(i+n+stime,i,-scost,0);
    }
    mcmf();
    printf("%lld\n",cost);
    return 0;
}
