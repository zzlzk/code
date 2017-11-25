#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

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

int n,m;

struct Edge {
    
    int u,v,next;
    
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
    
};

struct Lowest_Common_Ancestor {
    
    static const int MAXN=300010;
    static const int MAXM=600010;
    
    Edge edge[MAXM];
    
    int head[MAXN],cnt;
    int depth[MAXN],fa[MAXN],anc[MAXN][20];
    
    Lowest_Common_Ancestor() {cnt=0;}
    
    void addedge(int u,int v) {
        edge[++cnt]=Edge(u,v,head[u]);
        head[u]=cnt;
        return;
    }
    
    void dfs(int u,int f) {
        fa[u]=f;
        for(int i=head[u];i;i=edge[i].next) {
            int v=edge[i].v;
            if(v==f) continue;
            depth[v]=depth[u]+1;
            dfs(v,u);
        }
        return;
    }
    
    void Get_anc() {
        for(int i=1;i<=n;i++) {
            anc[i][0]=fa[i];
            for(int j=1;(1<<j)<=n;j++)
                anc[i][j]=-1;
        }
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i<=n;i++)
                if(anc[i][j-1]!=-1)
                    anc[i][j]=anc[anc[i][j-1]][j-1];
        return;
    }
    
    int LCA(int p,int q) {
        int LOG;
        if(depth[p]<depth[q]) swap(p,q);
        for(LOG=0;(1<<LOG)<=depth[p];LOG++);
        LOG--;
        for(int i=LOG;i>=0;i--)
            if(depth[p]-(1<<i)>=depth[q])
                p=anc[p][i];
        if(p==q) return q;
        for(int i=LOG;i>=0;i--)
            if(anc[p][i]!=-1&&anc[p][i]!=anc[q][i])
                p=anc[p][i],q=anc[q][i];
        return fa[p];
    }
    
}ans,a,b,c;

#define maxn Lowest_Common_Ancestor::MAXN 
#define maxm Lowest_Common_Ancestor::MAXM

int val[maxn],w[maxn],watch[maxn];
int P[maxm],Q[maxm];

void dfs(int u,int f) {
    int p=P[ans.depth[u]-w[u]+maxn];
    int q=Q[ans.depth[u]+w[u]];
    Q[ans.depth[u]]+=val[u];
    for(int i=a.head[u];i;i=a.edge[i].next)
        P[a.edge[i].v+maxn]++;
    for(int i=ans.head[u];i;i=ans.edge[i].next) {
        int v=ans.edge[i].v;
        if(v!=f) dfs(v,u);
    }
    watch[u]=P[ans.depth[u]-w[u]+maxn];
    watch[u]=watch[u]+Q[ans.depth[u]+w[u]]-p-q;
    for(int i=b.head[u];i;i=b.edge[i].next) {
        int v=b.edge[i].v;
        Q[v]--;
        if(v==ans.depth[u]+w[u])
            watch[u]--;
    }
    for(int i=c.head[u];i;i=c.edge[i].next)
        P[c.edge[i].v+maxn]--;
    return;
}

int main() {
    input(n),input(m);
    for(int i=1;i<n;i++) {
        int u,v;
        input(u),input(v);
        ans.addedge(u,v),
        ans.addedge(v,u);
    }
    for(int i=1;i<=n;i++)
        input(w[i]);
    ans.depth[1]=1;
    ans.dfs(1,0);
    ans.Get_anc();
    for(int i=1;i<=m;i++) {
        int s,t;
        input(s),input(t);
        int lca=ans.LCA(s,t);
        int dis=ans.depth[s]+ans.depth[t]-2*ans.depth[lca];
        int k=ans.depth[t]-dis;
        val[s]++;
        a.addedge(t,k),
        b.addedge(lca,ans.depth[s]),
        c.addedge(lca,k);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)
        printf("%d ",watch[i]);
    return 0;
}
