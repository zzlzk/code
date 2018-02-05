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
 
#define MAXN 610
#define MAXM 500010
 
struct Edge {
    int u,v,w,cap,next;
    Edge(int u=0,int v=0,int w=0,int cap=0,int next=0):
        u(u),v(v),w(w),cap(cap),next(next) {}
};
 
Edge edge[MAXM<<1];
int head[MAXN],cnt=1;
 
void addedge(int u,int v,int cap,int w) {
    edge[++cnt]=Edge(u,v,w,cap,head[u]),head[u]=cnt,
    edge[++cnt]=Edge(v,u,-w,0,head[v]),head[v]=cnt;
    return;
}
 
#define inf 2147483647
 
queue<int> q;
int dis[MAXN];
bool inq[MAXN];
int pre[MAXN],path[MAXN];
int n,m,src,decc;
 
bool spfa() {
    for(int i=0;i<=decc;i++)
        dis[i]=inf,pre[i]=-1,inq[i]=false;
    q.push(src),inq[src]=true,dis[src]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(edge[i].cap>0&&dis[v]>dis[u]+edge[i].w) {
                dis[v]=edge[path[v]=i].w+dis[pre[v]=u];
                if(!inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return pre[decc]!=-1;
}
 
int flow,cost;
 
void mcmf() {
    while(spfa()) {
        int f=inf;
        for(int u=decc;u!=src;u=pre[u])
            f=min(f,edge[path[u]].cap);
        flow+=f,cost+=dis[decc]*f;
        for(int u=decc;u!=src;u=pre[u]) {
            edge[path[u]].cap-=f,
            edge[path[u]^1].cap+=f;
        }
    }
    return;
}
 
const int dx[4]={0,0,-1,1};
const int dy[4]={-1,1,0,0};
int G[16][16],id[16][16];
 
int main() {
    src=0,decc=600;
    int n,m;
    input(n),input(m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            id[i][j]=(i-1)*m+j;
    char s[25];
    for(int i=1;i<=n;i++) {
        scanf("%s",s);
        for(int j=1;j<=m;j++)
            switch(s[j-1]) {
                case 'L': G[i][j]=0; break;
                case 'R': G[i][j]=1; break;
                case 'U': G[i][j]=2; break;
                case 'D': G[i][j]=3; break;
            }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<4;k++) {
                int x=i+dx[k],y=j+dy[k];
                x=(x>n?1:(x<1?n:x)),y=(y>m?1:(y<1?m:y));
                addedge(id[i][j],id[x][y]+300,1,k!=G[i][j]);
            }
    for(int i=1;i<=n*m;i++) {
        addedge(src,i,1,0),
        addedge(i+300,decc,1,0);
    }
    mcmf();
    printf("%d\n",cost);
    return 0;
}