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

struct Edge {
    int u,v,cap,next;
    Edge(int u=0,int v=0,int cap=0,int next=0):
        u(u),v(v),cap(cap),next(next) {}
};

Edge edge[2333333];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap) {
    edge[++cnt]=Edge(u,v,cap,head[u]);
    head[u]=cnt;
    return;
}

queue<int> q;
int lev[MAXN],cur[MAXN];
int n,m,k,src,decc;

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
            if(flow==used) break;
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

int fa[18];

int find(int x) {
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void Union(int x,int y) {
    x=find(x),y=find(y);
    if(x!=y) fa[x]=y;
    return;
}

int H[25],p[25],r[25][18];

int main() {
    input(n),input(m),input(k),n+=2;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) {
        input(H[i]),input(p[i]);
        for(int j=1;j<=p[i];j++) {
            input(r[i][j]);
            r[i][j]+=2;
            if(j!=1) Union(r[i][j],r[i][j-1]);
        }
    }
    if(find(1)!=find(2)) {
        puts("0");
        return 0;
    }
    src=9999,decc=10000;
    for(int day=0,sum=0;;day++) {
        addedge(src,day*n+2,inf),addedge(day*n+2,src,0),
        addedge(day*n+1,decc,inf),addedge(decc,day*n+1,0);
        if(day) {
            for(int i=1;i<=n;i++) {
                addedge((day-1)*n+i,day*n+i,inf),
                addedge(day*n+i,(day-1)*n+i,0);
            }
            for(int i=1,a,b;i<=m;i++) {
                a=r[i][((day-1)%p[i])+1],
                b=r[i][(day%p[i])+1],
                addedge((day-1)*n+a,day*n+b,H[i]),
                addedge(day*n+b,(day-1)*n+a,0);
            }
        }
        sum+=dinic();
        if(sum>=k) {
            printf("%d\n",day);
            break;
        }
    }
    return 0;
}
