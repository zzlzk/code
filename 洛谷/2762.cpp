#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
bool input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<48||c>57;c=getchar())
        if(c==45) a=-1;
    for(;c>=48&&c<=57;c=getchar())
        x=x*10+c-48;
    x*=a;
    return c!=10&&c!=13;
}

#define MAXN 110
#define MAXM 2610

struct Edge {
    int u,v,cap,next;
    Edge(int u=0,int v=0,int cap=0,int next=0):
        u(u),v(v),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap) {
    edge[++cnt]=Edge(u,v,cap,head[u]);
    head[u]=cnt;
    return;
}

queue<int> q;
int lev[MAXN],cur[MAXN];
int n,m,src,decc,N;

bool bfs() {
    for(int i=1;i<=N;i++)
        lev[i]=-1;
    while(!q.empty()) q.pop();
    q.push(src),lev[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&lev[v]==-1) {
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
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(edge[i].cap>0&&lev[v]==lev[u]+1) {
            x=dfs(v,min(edge[i].cap,flow-used));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(flow==used) break;
        }
    }
    if(x!=used) lev[u]=-1;
    return used;
}

#define inf 2147483647

int dinic() {
    int ans=0;
    while(bfs()) {
        for(int i=1;i<=N;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int main() {
    input(m),input(n);
    int ans=0;
    src=n+m+1,decc=n+m+2,N=n+m+2;
    for(int i=1,p,e;i<=m;i++) {
        input(p),ans+=p;
        addedge(src,i,p),addedge(i,src,0);
        bool flag=true;
        while(flag) {
            flag=input(e);
            addedge(i,e+m,inf),addedge(e+m,i,0);
        }
    }
    for(int i=1,c;i<=n;i++)
        input(c),addedge(i+m,decc,c),addedge(decc,i+m,0);
    ans-=dinic();
    for(int i=1;i<=m;i++)
        if(lev[i]!=-1) printf("%d ",i);
    puts("");
    for(int i=1;i<=n;i++)
        if(lev[i+m]!=-1) printf("%d ",i);
    printf("\n%d\n",ans);
    return 0;
}
