#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 5010 
#define maxm 50010 
#define inf 0x7fffffff
struct Edge {
    int u,v,cap,w,next;
    Edge(int u=0,int v=0,int cap=0,int w=0,int next=0):
        u(u),v(v),cap(cap),w(w),next(next) {}
}edge[maxm<<1];
int head[maxn],pre[maxn],dis[maxn],Path[maxn];
int flow,cost,n,m,s,t,cnt=1;
bool inq[maxn];
inline int input() {
    int x=0,a=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    return x*a;
}
inline void addedge(int u,int v,int cap,int w) {
    edge[++cnt]=Edge(u,v,cap,w,head[u]);
    head[u]=cnt;
    edge[++cnt]=Edge(v,u,0,-w,head[v]);
    head[v]=cnt;
    return;
}
inline void clear() {
    for(int i=1;i<=n;i++)
        dis[i]=inf,pre[i]=-1,inq[i]=false;
    return;
}
inline bool spfa() {
    clear();
    queue<int>q;
    dis[s]=0;
    q.push(s);
    inq[s]=true;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i;i=edge[i].next) {
            Edge e=edge[i];
            if(e.cap&&dis[u]+e.w<dis[e.v]) {
                dis[e.v]=dis[u]+e.w;
                pre[e.v]=u;
                Path[e.v]=i;
                if(inq[e.v]==false) {
                	q.push(e.v);
					inq[e.v]=true;	
				}
            }
        }
    }
    return pre[t]!=-1;
}
void MinCostMaxFlow() {
    while(spfa()) {
        int f=inf;
        for(int u=t;u!=s;u=pre[u])
            f=min(f,edge[Path[u]].cap);
        flow+=f;
        cost+=dis[t]*f;
        for(int u=t;u!=s;u=pre[u]) {
            edge[Path[u]].cap-=f;
            edge[Path[u]^1].cap+=f;
        }
    }
    return;
}
int main() {
    n=input();m=input();s=input();t=input();
    for(int i=1;i<=m;i++) {
        int u=input(),v=input(),cap=input(),w=input();
        addedge(u,v,cap,w); 
    }
    MinCostMaxFlow();
    printf("%d %d",flow,cost);
    return 0;
}
