#include<cmath>
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

#define MAXN 10010
#define MAXM 100010

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
    for(int i=1;i<=decc;i++) lev[i]=-1;
    while(!q.empty()) q.pop();
    q.push(src),lev[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&lev[v]==-1) {
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
        if(edge[i].cap>0&&lev[v]==lev[u]+1) {
            x=dfs(v,min(edge[i].cap,flow-used));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(used==flow) break;
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

int path[MAXN];
bool flag[MAXN];

int main() {
    input(n);
    src=10000,decc=10001;
    int ans=0,sum=0;
    while(true) {
        ans++,sum++;
        for(int i=1;i<sum;i++)
            if(sqrt(i+sum)==(int)sqrt(i+sum)) {
                addedge(i,sum+5000,1),
                addedge(sum+5000,i,0);
            }
        addedge(src,sum,1),addedge(sum,src,0),
        addedge(sum+5000,decc,1),addedge(decc,5000+sum,0);
        ans-=dinic();
        if(ans>n) break;
    }
    printf("%d\n",--sum);
    for(int u=1;u<=sum;u++)
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(!edge[i].cap) {
                path[u]=v-5000;
                break;
            }
        }
    for(int u=1;u<=sum;u++)
        if(!flag[u]) {
            for(int i=u;i;i=path[i])
                if(i!=5000) flag[i]=true,printf("%d ",i);
            puts("");
        }
    return 0;
}
