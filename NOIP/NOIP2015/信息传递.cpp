#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 200010
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
    
    int u,v,next;
    
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
    
}edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}

int ans=~0u>>1;
int dfn[MAXN],low[MAXN],timee;
int st[MAXN],top;
int col[MAXN],numcolor;

bool vis[MAXN],ins[MAXN];

void dfs(int now) {
    dfn[now]=low[now]=++timee;
    st[++top]=now;
    vis[now]=ins[now]=true;
    for(int i=head[now];i;i=edge[i].next) {
        int v=edge[i].v;
        if(ins[v]) low[now]=min(low[now],dfn[v]);
        else if(!vis[v]) {
            dfs(v);
            low[now]=min(low[now],low[v]);
        }
    }
    if(dfn[now]==low[now]) {
        int sum=1;
        col[now]=++numcolor;
        while(st[top]!=now) {
            col[st[top]]=numcolor;
            ins[st[top--]]=false;
            sum++;
        }
        ins[now]=false;
        top--;
        if(sum!=1) ans=min(ans,sum);
    }
    return;
}

int main() {
    int n;
    input(n);
    for(int u=1;u<=n;u++) {
        int v;
        input(v);
        addedge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i);
    printf("%d",ans);
    return 0;
}