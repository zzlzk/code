#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 50010

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

struct Node {
    
    int son,w;
    
    Node(int son=0,int w=0):
        son(son),w(w) {}
    
    bool operator < (const Node &q) const {
        return w < q.w;
    }
    
}b[MAXN<<1],c[MAXN<<1];

struct Edge {
    
    int u,v,w,Next;
    
    Edge(int u=0,int v=0,int w=0,int Next=0):
        u(u),v(v),w(w),Next(Next) {}
    
}edge[MAXN<<1];

int head[MAXN],cnt;
int a[MAXN],depth[MAXN];
int fa[MAXN][25],dis[MAXN][25];
bool vis[MAXN];

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

void dfs(int u) {
    for(int i=head[u];i;i=edge[i].Next) {
        int v=edge[i].v;
        if(!fa[v][0]) {
            fa[v][0]=u,
            depth[v]=depth[u]+1;
            dis[v][0]=edge[i].w;
            dfs(v);
        }
    }
    return;
}

void updata(int x) {
    int p=1,q=0;
    for(int i=head[x];i;i=edge[i].Next)
        if(edge[i].v!=fa[x][0]){
            updata(edge[i].v);
            p=p&vis[edge[i].v];
            q=1;
        }
    if(p&&q&&x!=1) vis[x]=1;
    return;
}

int n,m;
bool Judge(ll x) {
    memset(vis,0,sizeof(vis));
    int Cntb=0,Cntc=0;
    for(int i=1;i<=m;i++) {
        int y=a[i],z=0;
        for(int j=19;j>=0;j--)
            if(fa[y][j]&&dis[y][j]+z<=x)
                z+=dis[y][j],y=fa[y][j];
        if(y!=1) vis[y]=1;
        else {
            b[++Cntb].w=x-z;
            y=a[i];
            for(int j=19;j>=0;j--)
                if(fa[y][j]>1) y=fa[y][j];
            b[Cntb].son=y;
        }
    }
    updata(1);
    for(int i=head[1];i;i=edge[i].Next) {
        int v=edge[i].v;
        if(!vis[v]) c[++Cntc]=Node(v,edge[i].w);
    }
    sort(b+1,b+Cntb+1);
    sort(c+1,c+Cntc+1);
    c[Cntc+1].w=0x3f3f3f3f;
    int j=1;
    for(int i=1;i<=Cntb;i++) {
        if(!vis[b[i].son]) vis[b[i].son]=true;
        else if(b[i].w>=c[j].w) vis[c[j].son]=true;
        while(vis[c[j].son]) j++;
    }
    return j>Cntc;
}

int main() {
    ll l=0,r=0,ans=-1;
    input(n);
    for(int i=1;i<n;i++) {
        int u,v,w;
        input(u),input(v),input(w);
        addedge(u,v,w),
        addedge(v,u,w);
        r+=w;
    }
    input(m);
    for(int i=1;i<=m;i++)
        input(a[i]);
    depth[1]=1,fa[1][0]=1;
    dfs(1);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++) {
            fa[i][j]=fa[fa[i][j-1]][j-1],
            dis[i][j]=dis[i][j-1]+dis[fa[i][j-1]][j-1];
        }
    while(l<=r) {
        ll mid=l+r>>1;
        if(Judge(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}