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
 
struct Edge {
    int u,v,cap,next;
    Edge(int u=0,int v=0,int cap=0,int next=0):
        u(u),v(v),cap(cap),next(next) {}
};
 
Edge edge[MAXM<<1];
int head[MAXN],cnt=1;
 
void addedge(int u,int v,int cap) {
    edge[++cnt]=Edge(u,v,cap,head[u]),
    head[u]=cnt;
    return;
}
 
queue<int> q;
int lev[MAXN],cur[MAXN];
int n,m,src,decc,L;
 
bool bfs() {
    for(int i=1;i<=n;i++)
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
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}
 
struct Edges {
    int u,v,w;
    void scan() {
        input(u),input(v),input(w);
        return;
    }
    bool operator < (const Edges &q) const {
        return w<q.w;
    }
};
 
Edges a[MAXM];
 
int main() {
    input(n),input(m);
    for(int i=1;i<=m;i++) a[i].scan();
    sort(a+1,a+m+1),
    input(src),input(decc),input(L);
    for(int i=1;i<=m&&a[i].w<L;i++) {
        addedge(a[i].u,a[i].v,1),
        addedge(a[i].v,a[i].u,1);
    }
    int ans=dinic();
    memset(head,0,sizeof(head)),cnt=1;
    for(int i=m;i&&a[i].w>L;i--) {
        addedge(a[i].u,a[i].v,1),
        addedge(a[i].v,a[i].u,1);
    }
    printf("%d\n",ans+dinic());
    return 0;
}