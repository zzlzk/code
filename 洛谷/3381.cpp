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

#define MAXN 5010
#define MAXM 50010

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

#define inf 2147483647

queue<int> q;
int dis[MAXN];
bool inq[MAXN];
int pre[MAXN],path[MAXN];
int n,m,src,decc;

bool spfa() {
    for(int i=1;i<=n;i++)
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

int main() {
    input(n),input(m),input(src),input(decc);
    for(int u,v,w,cap;m;m--) {
        input(u),input(v),input(cap),input(w),
        addedge(u,v,w,cap),
        addedge(v,u,-w,0);
    }
    mcmf();
    printf("%d %d\n",flow,cost);
    return 0;
}
