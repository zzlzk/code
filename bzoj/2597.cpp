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
 
#define MAXN 11010
#define MAXM 30010
 
struct Edge {
    int u,v,cap,w,next;
    Edge(int u=0,int v=0,int cap=0,int w=0,int next=0):
        u(u),v(v),cap(cap),w(w),next(next) {}
};
  
Edge edge[MAXM<<1];
int head[MAXN],cnt=1;
  
void addedge(int u,int v,int cap,int w) {
    edge[++cnt]=Edge(u,v,cap,w,head[u]),head[u]=cnt,
    edge[++cnt]=Edge(v,u,0,-w,head[v]),head[v]=cnt;
    return;
}
 
 
int q[MAXN];
int dis[MAXN];
int pre[MAXN],path[MAXN];
bool inq[MAXN];
int src,decc;
  
#define inf 2147483647
  
bool spfa() {
    for(int i=src;i<=decc;i++)
        dis[i]=inf;
    int l=0,r=0;
    q[++r]=src,dis[src]=0,inq[src]=true;
    while(l!=r) {
        int u=q[l=(l+1==MAXN?0:l+1)];
        inq[u]=false;
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&dis[u]+edge[i].w<dis[v]) {
                dis[v]=edge[path[v]=i].w+dis[u];
                if(!inq[v]) {
                    q[r=(r+1==MAXN?0:r+1)]=v;
                    inq[v]=true;
                }
            }
        }
    }
    return dis[decc]!=inf;
}
  
int mcmf() {
    int cost=0;
    while(spfa()) {
        int flow=inf;
        for(int i=path[decc];i;i=path[edge[i].u])
            flow=min(flow,edge[i].cap);
        for(int i=path[decc];i;i=path[edge[i].u]) {
			cost+=flow*edge[i].w,
			edge[i].cap-=flow,edge[i^1].cap+=flow;
		}
    }
    return cost;
}
  
int G[110][110],Map[110][110];
  
#define calc(i,j) (n+(i>j?((j-1)*n+i):((i-1)*n+j)))
 
int main() {
    int n;
    input(n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            input(G[i][j]);
    src=0,decc=n*(n+1)+1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<n;j++)
            addedge(src,i,1,j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            if(G[i][j]==1||G[i][j]==2) {
                addedge(i,calc(i,j),1,0),
                Map[i][j]=cnt-1;
            }
            if(i<j) addedge(calc(i,j),decc,1,0);
        }
    printf("%d\n",n*(n-1)*(n-2)/6-mcmf());
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(j>1) putchar(' ');
            if(G[i][j]!=2) printf("%d",G[i][j]);
            else putchar(edge[Map[i][j]].cap?'0':'1');
        }
        puts("");
    }
    return 0;
}
