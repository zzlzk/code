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

#define MAXN 110010
#define MAXM 500010

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};

struct Edge {
    int u,v,w,next;
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
};

Edge edge[MAXM];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int N,K,A,B,C,s,t;
queue<int> q;
int dis[MAXN];
bool inq[MAXN];

#define inf 2147483647

int spfa() {
    for(int i=1;i<=t;i++)
        dis[i]=inf,inq[i]=false;
    q.push(s),inq[s]=true,dis[s]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u],v;i;i=edge[i].next) {
            v=edge[i].v;
            if(dis[v]>dis[u]+edge[i].w) {
                dis[v]=dis[u]+edge[i].w;
                if(!inq[v]) {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return inf;
}

int id(int x,int y,int d) {
    return d*N*N+(x-1)*N+y;
}

int G[110][110];

int main() {
    input(N),input(K),input(A),input(B),input(C);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            input(G[i][j]);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            for(int l=0;l<=K;l++) {
                if(l<K) addedge(id(i,j,l),id(i,j,K),G[i][j]?A:A+C);
                if((!G[i][j]&&l>0)||l==K) {
                    for(int k=0,x,y;k<4;k++) {
                        x=i+dx[k],y=j+dy[k];
                        if(x>0&&x<=N&&y>0&&y<=N)
                            addedge(id(i,j,l),id(x,y,l-1),k<2?0:B);
                    }
                }
            }
    s=id(1,1,K),t=id(N,N,K);
    int ans=spfa();
    for(int i=0;i<=K;i++)
        ans=min(ans,dis[id(N,N,i)]);
    printf("%d\n",ans);
    return 0;
}
