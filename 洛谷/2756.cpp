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

#define MAXN 10010
#define MAXM 100010

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
int n,m,src,decc;

bool bfs() {
    for(int i=1;i<=n+2;i++) lev[i]=-1;
    while(!q.empty()) q.pop();
    q.push(src),lev[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&lev[v]==-1) {
                q.push(v);
                lev[v]=lev[u]+1;
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
        if(edge[i].cap>0&&lev[v]==lev[u]+1) {
            x=dfs(v,min(edge[i].cap,flow-used)),
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(used==flow) break;
        }
    }
    if(x!=used) lev[u]=-1;
    return used;
}

#define inf 2147483647

int dinic(void) {
    int ans=0;
    while(bfs()) {
        for(int i=1;i<=n+2;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int main() {
    input(m),input(n);
    src=n+1,decc=n+2;
    for(int i,j;true;) {
        input(i),input(j);
        if(i==-1&&j==-1) break;
        addedge(i,j,1),addedge(j,i,0);
    }
    for(int i=1;i<=m;i++)
        addedge(src,i,1),addedge(i,src,0);
    for(int i=m+1;i<=n;i++)
        addedge(i,decc,1),addedge(decc,i,0);
    int ans=dinic();
    if(!ans) puts("No Solution!");
    else {
        printf("%d\n",ans);
        for(int i=2;i<=cnt;i+=2) {
            if(edge[i].u==src||edge[i].v==src) continue;
            if(edge[i].u==decc||edge[i].v==decc) continue;
            if(edge[i^1].cap==0) continue;
            printf("%d %d\n",edge[i].u,edge[i].v);
        }
    }
    return 0;
}
