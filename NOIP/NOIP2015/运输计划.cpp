#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 300010
#define MAXM 300010

template<typename T>
inline void input(T &x) {
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
    
}edge[MAXM<<2];

int head[MAXN],cnt;

inline void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int headQ[MAXN];

inline void add(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,headQ[u]);
    headQ[u]=cnt;
    return;
}

struct Query {
    
    int u,v;
    int dis,lca;
    
    bool operator <(const Query &w)const {
        return dis>w.dis;
    }
    
}q[MAXM];

int father[MAXN];

int Find(int x) {
    return father[x]==x?x:father[x]=Find(father[x]);
}

int depth[MAXN],val[MAXN];

void dfs(int u,int fa) {
    father[u]=u;
    for(int i=headQ[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(father[q[v].u]&&u==q[v].v)
            q[v].lca=Find(q[v].u);
        if(father[q[v].v]&&u==q[v].u)
            q[v].lca=Find(q[v].v);
    }
    for(int i=head[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(v==fa) continue;
        depth[v]=depth[u]+edge[i].w;
        dfs(v,u);
        val[v]=edge[i].w;
    }
    father[u]=fa;
    return;
}

int num[MAXN];

void DFS(int u,int fa) {
    for(int i=head[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(v==fa) continue;
        DFS(v,u);
        num[u]+=num[v];
    }
    return;
}

int n,m;

bool judge(int x) {
    int sum=0,Max=0;
    memset(num,0,sizeof(num));
    for(int i=1;i<=m;++i)
        if(q[i].dis>x) {
            ++sum;
            Max=max(Max,q[i].dis-x);
            ++num[q[i].u];++num[q[i].v];
            num[q[i].lca]-=2;
        } else break;
    DFS(1,1);
    for(int i=1;i<=n;++i)
        if(sum==num[i]&&val[i]>=Max)
            return true;
    return false;
}

int main() {
    input(n),input(m);
    for(int i=1;i<n;++i) {
        int u,v,w;
        input(u),input(v),input(w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=m;++i) {
        input(q[i].u),input(q[i].v);
        add(q[i].u,i,0);
        add(q[i].v,i,0);
    }
    dfs(1,1);
    int l=0,r=0,ans;
    for(int i=1;i<=m;++i) {
        q[i].dis=depth[q[i].u]+depth[q[i].v]-2*depth[q[i].lca];
        r=max(q[i].dis,r);
    }
    sort(q+1,q+m+1);
    while(l<=r) {
        int mid=l+r>>1;
        if(judge(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}