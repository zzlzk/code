#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 1010
#define MAXM 5010

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

template<typename Type>
struct Edge {
    int u,v,next,w;
    Type val;
    Edge(int u=0,int v=0,int w=0,int next=0,Type val=0):
        u(u),v(v),w(w),next(next),val(val) {}
};

#define Edge Edge<double>

Edge edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int n,m;
int f[MAXN];

void Get_Graph(double x) {
    for(int u=1;u<=n;u++)
        for(int i=head[u];i;i=edge[i].next)
            edge[i].val=edge[i].w*x-1.00*f[edge[i].v];
    return;
}

double dis[MAXN];
bool vis[MAXN],flag=false;

void spfa(int u) {
    vis[u]=true;
    for(int i=head[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(edge[i].val+dis[u]<dis[v]) {
            if(vis[v]) {
                flag=true;
                return;
            } else {
                dis[v]=edge[i].val+dis[u];
                spfa(v);
            }
        }
    }
    vis[u]=false;
    return;
}

bool Judge(double mid) {
    Get_Graph(mid);
    for(int i=1;i<=n;i++)
        dis[i]=vis[i]=0;
    flag=false;
    for(int i=1;i<=n;i++) {
        spfa(i);
        if(flag) return true;
    }
    return false;
}

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++)
        input(f[i]);
    for(int i=1,u,v,w;i<=m;i++) {
        input(u),input(v),input(w);
        addedge(u,v,w);
    }
    double l=0.0,r=10000.0,mid;
    while(r-l>0.001) {
        mid=(l+r)*0.5;
        if(Judge(mid)) l=mid;
        else r=mid;
    }
    printf("%.2lf",l);
    return 0;
}
