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
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 110
#define MAXM 5010

template<typename T>
struct Edge {
    int u,v,next;
    T w;
    Edge(int u=0,int v=0,T w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
};

Edge<int> edge[MAXM<<1];
int head[MAXN],cnt=0;
int id[MAXN][MAXN];

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge<int> (u,v,w,head[u]);
    head[u]=cnt;
    id[u][v]=cnt;
    return;
}

int n,m;
queue<int> q;
bool inq[MAXN],flag=true;
int dis[MAXN],pre[MAXN];

int spfa(int s=1,int t=n) {
    for(int i=1;i<=n;i++)
        dis[i]=~0u>>1,inq[i]=false;
    dis[s]=0;
    q.push(s);
    inq[s]=true;
    while(not q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i;i=edge[i].next) {
            int v=edge[i].v;
            if(dis[v]>dis[u]+edge[i].w) {
                dis[v]=dis[u]+edge[i].w;
                if(flag) pre[v]=u;
                if(not inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return dis[t];
}


int main() {
    input(n),input(m);
    for(int i=1,u,v,w;i<=m;i++) {
        input(u),input(v),input(w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    int ans=spfa(),Max=-1;
    flag=false;
    for(int i=n,id1,id2;i!=1;i=pre[i]) {
        id1=id[i][pre[i]],id2=id[pre[i]][i];
        edge[id1].w<<=1,edge[id2].w<<=1;
        Max=max(Max,spfa());
        edge[id1].w>>=1,edge[id2].w>>=1;
    }
    printf("%d\n",Max-ans);
    return 0;
}
