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

#define MAXN 1020 
#define MAXM 20010

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
int lev[MAXN],cur[MAXN];
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
            x=dfs(v,min(edge[i].cap,flow-used));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(used==flow) break;
        }
    }
    if(used!=flow) lev[u]=-1;
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

int main() {
    input(m),input(n);
    decc=n+m+2,src=n+m+1;
    int sum=0;
    for(int i=1,x;i<=m;i++) {
        input(x),sum+=x,
        addedge(src,i,x),addedge(i,src,0);
    }
    for(int i=1,p,x;i<=n;i++) {
        for(input(p);p;p--) {
            input(x),
            addedge(x,i+m,1),addedge(i+m,x,0);
        }
        addedge(i+m,decc,1),addedge(decc,i+m,0);
    }
    if(sum!=dinic()) puts("No Solution!");
    else {
        for(int u=1;u<=m;u++) {
            printf("%d:",u);
            for(int i=head[u];i;i=edge[i].next)
                if(edge[i].v!=src&&edge[i].cap==0)
                    printf(" %d",edge[i].v-m);
            puts("");
        }
    }
    return 0;
}
