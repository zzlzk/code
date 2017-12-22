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

#define MAXN 40010
#define MAXM 400010

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
    for(int i=0;i<=decc;i++)
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
        if(edge[i].cap>0&&lev[v]==lev[u]+1) {
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

int col[210][210];

bool can(int x,int y) {
    return col[x][y]!=233&&x>0&&x<=n&&y>0&&y<=n;
}

const int dx[8]={2,2,-2,-2,1,1,-1,-1};
const int dy[8]={1,-1,1,-1,2,-2,2,-2};

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++) {
        col[i][1]=i==1?1:3-col[i-1][1];
        for(int j=2;j<=n;j++)
            col[i][j]=3-col[i][j-1];
    }
    for(int i=1,x,y;i<=m;i++) {
        input(x),input(y),
        col[x][y]=233;
    }
    src=n*n+1,decc=n*n+2;
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++) {
            x=(i-1)*n+j;
            if(col[i][j]==1) {
                addedge(src,x,1),
                addedge(x,src,0);
                for(int k=0,y;k<8;k++)
                    if(can(i+dx[k],j+dy[k])) {
                        y=(i+dx[k]-1)*n+j+dy[k],
                        addedge(x,y,1),
                        addedge(y,x,0);
                    }
            } else if(col[i][j]==2) {
                addedge(x,decc,1),
                addedge(decc,x,0);
            }
        }
    printf("%d\n",n*n-m-dinic());
    return 0;
}
