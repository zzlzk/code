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
 
#define MAXN 6510
#define MAXM 11010
 
struct Edge {
    int u,v,w,cap,next;
    Edge(int u=0,int v=0,int w=0,int cap=0,int next=0):
        u(u),v(v),w(w),cap(cap),next(next) {}
};
 
Edge edge[MAXM<<1];
int head[MAXN],cnt=1;
 
void addedge(int u,int v,int cap,int w) {
    edge[++cnt]=Edge(u,v,w,cap,head[u]),head[u]=cnt,
    edge[++cnt]=Edge(v,u,-w,0,head[v]),head[v]=cnt;
    return;
}
 
#define inf 2147483647
 
queue<int> q;
int dis[MAXN];
bool inq[MAXN];
int pre[MAXN],path[MAXN];
int n,m,src,decc;
 
bool spfa() {
    for(int i=0;i<=decc;i++)
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
 
int mcmf() {
    int cost=0;
    while(spfa()) {
        int f=inf;
        for(int u=decc;u!=src;u=pre[u])
            f=min(f,edge[path[u]].cap);
        cost+=dis[decc]*f;
        for(int u=decc;u!=src;u=pre[u]) {
            edge[path[u]].cap-=f,
            edge[path[u]^1].cap+=f;
        }
    }
    return cost;
}
 
int win[MAXN],lose[MAXN];
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
 
int sqr(int x) {
    return x*x;
}
 
int main() {
    int n,m;
    input(n),input(m);
    src=n+m+1,decc=src+1;
    for(int i=1;i<=n;i++) {
        input(win[i]),input(lose[i]),
        input(c[i]),input(d[i]);
    }
    for(int i=1;i<=m;i++) {
        input(a[i]),input(b[i]),
        lose[a[i]]++,lose[b[i]]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=c[i]*sqr(win[i])+d[i]*sqr(lose[i]);
    for(int i=1;i<=m;i++) {
        addedge(src,i,1,0),
        addedge(i,a[i]+m,1,0),
        addedge(i,b[i]+m,1,0);
        int tmp=c[a[i]]*(win[a[i]]<<1|1)-d[a[i]]*((lose[a[i]]<<1)-1);
        addedge(a[i]+m,decc,1,tmp),
        win[a[i]]++,lose[a[i]]--,
        tmp=c[b[i]]*(win[b[i]]<<1|1)-d[b[i]]*((lose[b[i]]<<1)-1),
        addedge(b[i]+m,decc,1,tmp);
        win[b[i]]++,lose[b[i]]--;
    }
    printf("%d\n",ans+mcmf());
    return 0;
}