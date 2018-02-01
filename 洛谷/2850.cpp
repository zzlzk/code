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

#define MAXN 510
#define MAXM 5210

struct Edge {
    int u,v,w,next;
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
};

Edge edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int dis[MAXN];
bool vis[MAXN],flag=false;

void spfa(int u) {
    if(flag) return;
    vis[u]=true;
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(dis[u]+edge[i].w<dis[v]) {
            dis[v]=edge[i].w+dis[u];
            if(vis[v]) {
                flag=true;
                return;
            }
            spfa(v);
            if(flag) return;
        }
    }
    vis[u]=false;
    return;
}

void Clear() {
    flag=false,cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,0,sizeof(head));
    memset(dis,0,sizeof(dis));
    return;
}

int main() {
    int T;
    for(input(T);T;T--,Clear()) {
        int n,m1,m2;
        input(n),input(m1),input(m2);
        for(int i=1,u,v,w;i<=m1;i++) {
            input(u),input(v),input(w),
            addedge(u,v,w),addedge(v,u,w);
        }
        for(int i=1,u,v,w;i<=m2;i++) {
            input(u),input(v),input(w),
            addedge(u,v,-w);
        }
        for(int i=1;i<=n&&!flag;i++) spfa(i);
        puts(flag?"YES":"NO");
    }
    return 0;
}
