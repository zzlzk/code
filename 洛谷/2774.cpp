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
#define MAXM 50010
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};

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
        for(int i=0;i<=decc;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int col[110][110];

bool inmap(int x,int y) {
    return x>0&&x<=n&&y>0&&y<=m;
}

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++) {
        col[i][1]=i==1?1:3-col[i-1][1];
        for(int j=2;j<=m;j++)
            col[i][j]=3-col[i][j-1];
    }
    int sum=0;
    src=(n-1)*m+m+1,decc=(n-1)*m+m+2;
    for(int i=1,x,val;i<=n;i++)
        for(int j=1;j<=m;j++) {
            input(val),sum+=val,x=(i-1)*m+j;
            if(col[i][j]==1) {
                addedge(src,x,val),addedge(x,src,0);
                for(int k=0,y;k<4;k++)
                    if(inmap(i+dx[k],j+dy[k])) {
                        y=(i+dx[k]-1)*m+j+dy[k],
                        addedge(x,y,inf),
                        addedge(y,x,0);
                    }
            } else {
                addedge(x,decc,val),
                addedge(decc,x,0);
            }
        }
    printf("%d\n",sum-dinic());
    return 0;
}
