#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename ____>
void _____(____ &___) {
    ___=0; ____ __=1;
    register char _=getchar();
    for(;_<'0'||_>'9';_=getchar())
        if(_=='-') __=-1;
    for(;_>='0'&&_<='9';_=getchar())
        ___=___*10+_-'0';
    ___*=__;
    return;
}

#define MAXN 10010
#define MAXM 50010

struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};

Edge edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}

int dfn[MAXN],low[MAXN],timee;
int st[MAXN],top;
int col[MAXN],numcolor;
bool vis[MAXN],ins[MAXN];
int num[MAXN];

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
        col[now]=++numcolor;
        num[numcolor]++;
        while(st[top]!=now) {
            col[st[top]]=numcolor;
            num[numcolor]++;
            ins[st[top--]]=false;
        }
        ins[now]=false;
        top--;
    }
    return;
}


int outdeg[MAXN];

int main() {
    int n,m;
    _____(n),_____(m);
    for(int i=1,A,B;i<=m;i++) {
        _____(A),_____(B);
        addedge(A,B);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i);
    for(int u=1;u<=n;u++)
        for(int i=head[u];i;i=edge[i].next)
            if(col[u]!=col[edge[i].v])
                outdeg[col[u]]++;
    int sum=0,color;
    for(int i=1;i<=numcolor;i++)
        if(outdeg[i]==0) sum++,color=i;
    if(sum==1) printf("%d\n",num[color]);
    else printf("0");
    return 0;
}
