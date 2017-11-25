#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
#define MAXN 40
#define MAXM 40
#define MAXQ 510
#define inf 0x7fffffff

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

struct Edge {
    
    int u,v,w,next;
    
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
    
}edge[20010];
int head[3610],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int n,m,QQ;

int GetID(int i,int j) {
    j--;
    return (i-1)*m+j<<2; 
}

struct Point {
    
    int x,y;
    
    Point(int x=0,int y=0):
        x(x),y(y) {}
    
}cur,nxt;

queue<Point> Q;

bool a[MAXN][MAXM];

int predis[MAXN][MAXN];

int GetID(Point A) {
    return GetID(A.x,A.y);
}

#define opp(d) ((d+2)%4)

void bfs(Point E,Point P,int d) {
    memset(predis,-1,sizeof(predis));
    predis[P.x][P.y]=1;
    predis[E.x][E.y]=0;
    Q.push(E);
    while(!Q.empty()) {
        Point u=Q.front();
        Q.pop();
        for(int i=0;i<4;i++) {
            Point v=Point(u.x+dx[i],u.y+dy[i]);
            if(a[v.x][v.y]&&predis[v.x][v.y]==-1) {
                predis[v.x][v.y]=predis[u.x][u.y]+1;
                Q.push(v);
            }
        }
    }
    if(d==inf) return;
    int id=GetID(P);
    for(int i=0;i<4;i++) {
        int x=P.x+dx[i],y=P.y+dy[i];
        if(predis[x][y]>0)
            addedge(id+d,id+i,predis[x][y]);
    }
    addedge(id+d,GetID(E)+opp(d),1);
    return;
}

void bfs(int ex,int ey,int px,int py,int d) {
    Point E=Point(ex,ey);
    Point P=Point(px,py);
    bfs(E,P,d);
    return;
}

queue<int> q;

bool inq[3610];

int dis[3610];

void spfa(Point S) {
    memset(dis,-1,sizeof(dis));
    for(int i=0; i<4; ++i) {
        int x=S.x+dx[i],y=S.y+dy[i];
        if(predis[x][y]!=-1) {
            int id=GetID(S)+i;
            dis[id]=predis[x][y];
            q.push(id);
        }
    }
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i;i=edge[i].next) {
            int v=edge[i].v;
            if(dis[v]==-1||dis[v]>dis[u]+edge[i].w) {
                dis[v]=dis[u]+edge[i].w;
                if(!inq[v]) {
                    inq[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return;
}

int main() {
    input(n),input(m),input(QQ);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]) {
                if(a[i-1][j]) bfs(i-1,j,i,j,0); 
                if(a[i][j+1]) bfs(i,j+1,i,j,1);
                if(a[i+1][j]) bfs(i+1,j,i,j,2);
                if(a[i][j-1]) bfs(i,j-1,i,j,3);
            }
    while(QQ--) {
        Point E,S,T;
        input(E.x),input(E.y);
        input(S.x),input(S.y);
        input(T.x),input(T.y);
        if(S.x==T.x&&S.y==T.y) {
            printf("0\n");
            continue;
        }
        bfs(E,S,inf);
        spfa(S);
        int ans=inf;
        int id=GetID(T);
        for(int i=0;i<4;i++)
            if(dis[id+i]!=-1)
                ans=min(ans,dis[id+i]);
        printf("%d\n",ans==inf?-1:ans);
    }
    return 0;
}