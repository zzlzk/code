#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

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

#define MAXN 100010
#define MAXM 200010

struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};

Edge edge[MAXM];
int head[MAXN],cnt;
int indeg[MAXN],outdeg[MAXN];
int remember[MAXN];

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}

int dfs(int now) {
    if(remember[now])
        return remember[now];
    int ans=0;
    if(!outdeg[now]&&indeg[now])
        ans=1;
    for(int i=head[now];i;i=edge[i].next)
        ans+=dfs(edge[i].v);
    return remember[now]=ans;
}

int main() {
    int n,m;
    input(n),input(m);
    for(int i=1,u,v;i<=m;i++) {
        input(u),input(v);
        indeg[v]++;
        outdeg[u]++;
        addedge(u,v);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(!indeg[i])
            ans+=dfs(i);
    printf("%d\n",ans);
    return 0;
}
