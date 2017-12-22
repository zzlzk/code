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
#define MAXM 10210

struct Edge {
    int u,v,w,cap,next;
    Edge(int u=0,int v=0,int w=0,int cap=0,int next=0):
        u(u),v(v),w(w),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int w,int cap) {
    edge[++cnt]=Edge(u,v,w,cap,head[u]);
    head[u]=cnt;
    return;
}

queue<int> q;
int dis[MAXN];
bool inq[MAXN];
int path[MAXN],pre[MAXN];
int n,m,src,decc;

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

int flow,cost;

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

int a[110],b[110];
int c[110][110];

int main() {
    input(m),input(n);
    for(int i=1;i<=m;i++) input(a[i]);
    for(int i=1;i<=n;i++) input(b[i]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            input(c[i][j]);
    src=n+m+1,decc=n+m+2;
    for(int i=1;i<=m;i++)
        addedge(src,i,0,a[i]),addedge(i,src,0,0);
    for(int i=1;i<=n;i++)
        addedge(i+m,decc,0,b[i]),addedge(decc,i+m,0,0);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            addedge(i,j+m,c[i][j],inf),addedge(j+m,i,-c[i][j],0);
    mcmf();
    printf("%d\n",cost);
    for(int i=1;i<=decc;i++)
        head[i]=0;
    cnt=1,flow=cost=0;
    for(int i=1;i<=m;i++)
        addedge(src,i,0,a[i]),addedge(i,src,0,0);
    for(int i=1;i<=n;i++)
        addedge(i+m,decc,0,b[i]),addedge(decc,i+m,0,0);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            addedge(i,j+m,-c[i][j],inf),addedge(j+m,i,c[i][j],0);
    mcmf();
    printf("%d\n",-cost);
    return 0;
}
