#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 600
#define inf 0x7fffffff
struct Edge {
    int u,v,cap,next;
    Edge(int u=0,int v=0,int cap=0,int next=0):
        u(u),v(v),cap(cap),next(next) {}
}edge[maxn*maxn];
int head[maxn],agt[maxn];
int cnt=1,S,T;
inline bool input(int &x) {
    x=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    if(c==10||c==13) return false;
    return true;
}
inline void addedge(int u,int v,int cap) {
    edge[++cnt]=Edge(u,v,cap,head[u]);
    head[u]=cnt;
    edge[++cnt]=Edge(v,u,0,head[v]);
    head[v]=cnt;
    return;
}
inline void clear() {
    memset(agt,0,sizeof(agt));
    return;
}
inline bool bfs() {
    clear();
    queue<int>q;
    q.push(S);
    agt[S]=1;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=edge[i].next)
            if(edge[i].cap&&!agt[edge[i].v]) {
                agt[edge[i].v]=agt[u]+1;
                q.push(edge[i].v);
            }
    }
    return agt[T];
}
int dfs(int x,int maxflow) {
    if(!maxflow||x==T) return maxflow;
    int used=0;
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].cap&&agt[edge[i].v]==agt[x]+1) {
            int flow=dfs(edge[i].v,min(maxflow,edge[i].cap));
            used+=flow;
            maxflow-=flow;
            edge[i].cap-=flow;
            edge[i^1].cap+=flow;
        }
    return used;
}
inline int dinic() {
    int ans=0;
    while(bfs()) ans+=dfs(S,inf);
    return ans;
}
int main() {
    int m,n,ans=0;
    input(m),input(n);
    S=0,T=n+m+1;
    for(int i=1,w,x;i<=m;i++) {
        input(w);
        ans+=w;
        addedge(S,i,w);
        bool flag=true;
        while(flag) {
            flag=input(x); 
            addedge(i,x+m,inf);
        }
    }
    for(int i=1,cost;i<=n;i++) {
        input(cost);
        addedge(m+i,T,cost);
    }
    ans-=dinic();
    for(int i=1;i<=m;i++)
        if(agt[i]!=0) printf("%d ",i);
    printf("\n");
    for(int i=m+1;i<T;i++)
        if(agt[i]!=0) printf("%d ",i-m);
    printf("\n%d",ans);
    return 0;
}
