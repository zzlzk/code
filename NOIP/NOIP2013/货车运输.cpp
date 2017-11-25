#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 10010
#define MAXM 50010

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
    
    bool operator < (const Edge &q)const {
        return w>q.w;
    }
    
}edge[MAXN<<1],e[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt++;
    return;
}

int father[MAXN],n,m;

int Find(int x) {
    return father[x]==x?x:father[x]=Find(father[x]);
}

void Kruskal_Build_tree() {
    for(int i=1;i<=n;i++) father[i]=i,head[i]=-1;
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++) {
        int fu=Find(e[i].u),fv=Find(e[i].v);
        if(fu!=fv) {
            addedge(e[i].u,e[i].v,e[i].w);
            addedge(e[i].v,e[i].u,e[i].w);
            father[fu]=fv;
        }
    }
    return;
}

int depth[MAXN];
int fa[MAXN][31],dis[MAXN][31];

void dfs(int u,int p) {
    for(int i=head[u];~i;i=edge[i].next)
        if(i!=p) {
            int v=edge[i].v;
            depth[v]=depth[u]+1;
            fa[v][0]=u;
            dis[v][0]=edge[i].w;
            dfs(v,i^1);
        }
    return;
}

int lca(int x,int y) {
    int ans=~0u>>1;
    if(depth[x]>depth[y]) swap(x,y);
    for(int i=15;i>=0;i--)
        if(depth[fa[y][i]]>=depth[x]) {
            ans=min(ans,dis[y][i]);
            y=fa[y][i];
        }
    if(x==y) return ans;
    for(int i=15;i>=0;i--)
        if(fa[x][i]!=fa[y][i]) {
            ans=min(ans,min(dis[x][i],dis[y][i]));
            x=fa[x][i];
            y=fa[y][i];
        }
    if(!fa[x][0]) return -1;
    return min(ans,min(dis[x][0],dis[y][0]));
}

int main() {
    input(n),input(m);
    for(int i=1;i<=m;i++)
        input(e[i].u),input(e[i].v),input(e[i].w);
    Kruskal_Build_tree();
    dfs(depth[1]=1,-1);
    for(int j=1;j<=15;j++)
        for(int i=1;i<=n;i++) {
            fa[i][j]=fa[fa[i][j-1]][j-1];
            dis[i][j]=min(dis[i][j-1],dis[fa[i][j-1]][j-1]);
        }
    int Q;
    input(Q);
    while(Q--) {
        int x,y;
        input(x),input(y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}