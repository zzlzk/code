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
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 1010
#define MAXM 10010
#define inf 0x7fffffff

struct Edge {
    int u,v,w,next;
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int n,m,k;
int dis[MAXN];
queue<int> q;
bool inq[MAXN];

void spfa(int mid,int s=1,int t=n) {
    for(int i=1;i<=n;i++)
        dis[i]=inf,inq[i]=false;
    q.push(s);
    dis[s]=0;
    inq[s]=true;
    while(not q.empty()) {
        int u=q.front(),w,v;
        q.pop();
        inq[u]=false;
        for(int i=head[u];i;i=edge[i].next) {
            v=edge[i].v;
            w=edge[i].w>mid?1:0;
            if(dis[v]>dis[u]+w) {
                dis[v]=dis[u]+w;
                if(!inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return;
}

bool Judge(int mid) {
    spfa(mid);
    return dis[n]<=k;
}

int main() {
    int l=0,r=-1;
    input(n),input(m),input(k);
    for(int i=1,u,v,w;i<=m;i++) {
        input(u),input(v),input(w);
        addedge(u,v,w);
        addedge(v,u,w);
        r=max(r,w);
    }
    int mid,ans=-1;
    while(l<=r) {
        mid=l+r>>1;
        if(Judge(mid)) {
            ans=mid,r=mid-1;
        } else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
