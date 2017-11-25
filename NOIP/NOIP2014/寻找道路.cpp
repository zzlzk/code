#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define inf 0x7fffffff
#define MAXN 10010
#define MAXM 200010

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

struct Edge {
    
    int u,v,w,next;
    
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
    
}edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int vis[MAXN],indeg[MAXN];

void dfs(int now) {
    if(vis[now]++) return;
    for(int i=head[now];i;i=edge[i].next)
        dfs(edge[i].v);
    return;
}

queue<int> q;

int n,m;
int dis[MAXN];

bool inq[MAXN];

int spfa(int s,int t) {
    for(int i=1;i<=n;i++) dis[i]=inf;
    q.push(s);
    inq[s]=true;
    dis[s]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i;i=edge[i].next) {
            int v=edge[i].v;
            if(vis[v]!=indeg[v]) continue;
            if(dis[u]+edge[i].w<dis[v]) {
                dis[v]=dis[u]+edge[i].w;
                if(!inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return dis[t]==inf?-1:dis[t];
}

int main() {
    input(n),input(m);
    for(int i=1;i<=m;i++) {
        int u,v;
        input(u),input(v);
        swap(u,v);
        addedge(u,v,1);
        indeg[v]++;
    }
    int s,t;
    input(s),input(t);
    swap(s,t);
    dfs(s);
    printf("%d",spfa(s,t));
    return 0;
}
