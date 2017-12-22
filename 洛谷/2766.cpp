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

#define MAXN 1010
#define MAXM 250510

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
int cur[MAXN],lev[MAXN];
int n,m,src,decc;

bool bfs() {
    for(int i=1;i<=decc;i++)
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
                q.push(v);
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
        if(lev[v]==lev[u]+1&&edge[i].cap>0) {
            x=dfs(v,min(flow-used,edge[i].cap));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(flow==used) break;
        }
    }
    if(flow!=used) lev[u]=-1;
    return used;
}

#define inf 2147483647

int dinic() {
    int ans=0;
    while(bfs()) {
        for(int i=1;i<=decc;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int f[510],a[510];

int main() {
    input(n);
    for(int i=1;i<=n;i++)
        input(a[i]);
    int ans=1;
    for(int i=1;i<=n;i++) {
        f[i]=1;
        for(int j=1;j<i;j++)
            if(a[i]>=a[j]) f[i]=max(f[i],f[j]+1);
        ans=max(ans,f[i]);
    }
    printf("%d\n",ans);
    src=n<<1|1,decc=n+1<<1;
    for(int i=1;i<=n;i++) {
        if(f[i]==1) {
            addedge(src,i,1),
            addedge(i,src,0);
        }
        if(f[i]==ans) {
            addedge(i+n,decc,1),
            addedge(decc,i+n,0);
        }
        addedge(i,i+n,1),addedge(i+n,i,0);
        for(int j=1;j<i;j++)
            if(a[i]>=a[j]&&f[i]==f[j]+1) {
                addedge(j+n,i,1),
                addedge(i,j+n,0);
            }
    }
    int ans2=dinic();
    printf("%d\n",ans2);
    addedge(1,1+n,inf),addedge(n+1,1,0),
    addedge(src,1,inf),addedge(1,src,0);
    addedge(n,n<<1,inf),addedge(n<<1,n,0);
    if(f[n]==ans) addedge(n<<1,decc,inf),addedge(decc,n<<1,0);
    printf("%d\n",ans2+dinic());
    return 0;
}
