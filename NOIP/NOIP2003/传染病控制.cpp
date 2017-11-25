#include<cstdio>
using namespace std;
#define maxn 310
#define maxm 200010
#define inf 0x7fffffff
struct Edge{
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
}edge[maxm];
int head[maxn],cnt,ans=inf,n,p;
int father[maxn],depth[maxn];
bool pd[maxn][maxn],mark[maxn],check[maxn];
inline void Add_edge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    pd[u][v]=true;
    edge[++cnt]=Edge(v,u,head[v]);
    head[v]=cnt;
    pd[v][u]=true;
    return;
}
void Build(int u) {
    if(mark[u]) return;
    mark[u]=true;
    for(int i=head[u];i>0;i=edge[i].next) {
        int v=edge[i].v;
        if(!mark[v]) {
            father[v]=u;
            depth[v]=depth[u]+1;
            Build(v);
        }
    }
    return;
}
void dfs(int index,int nowans) {
    bool flag=true;
    if(nowans>=ans) return;
    for(int i=1;i<=n;i++)
        if(depth[i]==index&&check[i])
            for(int j=head[i];j;j=edge[j].next) {
                int v=edge[j].v;
                if(father[v]==i) {
                    flag=false;
                    check[v]=true;
                    nowans++;
                }
            }
    nowans--;
    for(int i=1;i<=n;i++)
        if(depth[i]==index+1&&check[i]) {
            check[i]=false;
            dfs(index+1,nowans);
            check[i]=true;
        }
    nowans++;
    for(int i=1;i<=n;i++)
        if(depth[i]==index&&check[i])
            for(int j=head[i];j;j=edge[j].next) {
                int v=edge[j].v;
                if(father[v]==i) {
                    check[v]=false;
                    nowans--;
                }
            }
    if(flag==true&&nowans<ans) ans=nowans;
    return;
}
int main() {
    scanf("%d%d",&n,&p);
    for(int i=1;i<=p;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        if(!pd[u][v]) Add_edge(u,v);
    }
    depth[1]=1;
    check[1]=true;
    Build(1);
    dfs(1,1);
    printf("%d",ans);
    return 0;
}
