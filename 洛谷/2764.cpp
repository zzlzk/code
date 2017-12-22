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

#define MAXN 310
#define MAXM 6310

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
    for(int i=1;i<=n+1<<1;i++)
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

int Path[MAXN];
bool flag[MAXN];

int dfs(int u,int flow) {
    if(u==decc) return flow;
    int x,used=0;
    for(int &i=cur[u];i;i=edge[i].next) {
        int v=edge[i].v;
        if(edge[i].cap>0&&lev[v]==lev[u]+1) {
            x=dfs(v,min(edge[i].cap,flow-used));
            used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
            if(x) {
				Path[u]=v;
				if(v>n) flag[v-n]=true; 
			}
            if(used==flow) break;
        }
    }
    if(x!=used) lev[u]=-1;
    return used;
}

#define inf 2147483647

int dinic() {
    int ans=0;
    while(bfs()) {
        for(int i=1;i<=n+1<<1;i++)
            cur[i]=head[i];
        ans+=dfs(src,inf);
    }
    return ans;
}

int main() {
    input(n),input(m);
    for(int i=1,u,v;i<=m;i++) {
        input(u),input(v),
        addedge(u,v+n,1),addedge(v+n,u,0);
    }
    src=(n<<1)+1,decc=(n<<1)+2;
    for(int i=1;i<=n;i++) {
        addedge(src,i,1),addedge(i,src,0),
        addedge(i+n,decc,1),addedge(decc,i+n,0);
    }
    int ans=dinic();
    for(int u=1;u<=n;u++)
        if(!flag[u]) {
            printf("%d",u);
			for(int k=u;Path[k];k=Path[k]-n)
				printf(" %d",Path[k]-n);
            printf("\n");
        }
    printf("%d\n",n-ans);
    return 0;
}

