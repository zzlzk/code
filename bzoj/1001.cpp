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

#define MAXN 1000010
#define MAXM 3000010

struct Edge {
    int u,v,cap,next;
    Edge(int u=0,int v=0,int cap=0,int next=0):
        u(u),v(v),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap) {
    edge[++cnt]=Edge(u,v,cap,head[u]),head[u]=cnt;
    return;
}

queue<int> q;
int lev[MAXN],cur[MAXN];
int src,decc;

bool bfs() {
    for(int i=src;i<=decc;i++)
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
        for(int i=src;i<=decc;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int main() {
    int n,m,x;
    input(n),input(m),src=1,decc=n*m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++) {
            input(x),
            addedge(m*(i-1)+j,m*(i-1)+j+1,x),
            addedge(m*(i-1)+j+1,m*(i-1)+j,x);
        }
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++) {
            input(x),
            addedge(m*(i-1)+j,m*(i)+j,x);
            addedge(m*(i)+j,m*(i-1)+j,x);
        }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++) {
            input(x),
            addedge(m*(i-1)+j,m*(i)+j+1,x);
            addedge(m*(i)+j+1,m*(i-1)+j,x);
        }
    printf("%d\n",dinic());
    return 0;
}
