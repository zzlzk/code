#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 10
#define maxm 10
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};

struct Point {
    int x,y;
    Point(int x=0,int y=0):
        x(x),y(y) {}
}ans[maxn];

int N;
int G[maxn][maxm],op[maxn];
bool can[maxn][maxm],vis[maxn][maxm];

void down() {
    int tmp[maxm];
    for(int i=1;i<=5;i++) {
        int cnt=0;
        for(int j=1;j<=7;j++) {
            if(G[i][j])
                tmp[++cnt]=G[i][j];
            G[i][j]=0;
        }
        for(int j=1;j<=cnt;j++)
            G[i][j]=tmp[j];
    }
    return;
}

bool dfs(Point u,int &cnt,int st) {
    vis[u.x][u.y]=true;
    for(int i=0;i<4;i++) {
        Point v=Point(u.x+dx[i],u.y+dy[i]);
        if(G[v.x][v.y]&&G[v.x][v.y]==st&&!vis[v.x][v.y]) {
            int t=G[v.x][v.y];
            G[v.x][v.y]=0;
            vis[v.x][v.y]=true;
            dfs(v,++cnt,st);
            vis[v.x][v.y]=false;
            if(cnt<3) G[v.x][v.y]=t;
        }
    }
    vis[u.x][u.y]=0;
    return cnt>=3;
}

bool clean() {
    memset(can,0,sizeof(can));
    bool flag=false;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
            if(G[i][j]&&G[i][j]==G[i][j+1]&&G[i][j]==G[i][j+2]) {
                flag=true;
                can[i][j]=can[i][j+1]=can[i][j+2]=true;
                for(int k=j+3;k<=7&&G[i][k]==G[i][j];k++)
                    can[i][k]=true;
            }
    for(int j=1;j<=7;j++)
        for(int i=1;i<=3;i++)
            if(G[i][j]&&G[i][j]==G[i+1][j]&&G[i][j]==G[i+2][j]) {
                flag=true;
                can[i][j]=can[i+1][j]=can[i+2][j]=true;
                for(int k=i+3;k<=5&&G[k][j]==G[i][j];k++)
                    can[k][j]=true;
            }
    if(!flag) return false;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++)
            if(can[i][j]) G[i][j]=0;
    return true;
}

void move_block(Point a,int dir) {
    swap(G[a.x+dir][a.y],G[a.x][a.y]);
    while(true) {
        down();
        if(!clean()) break;
    }
    return;
}

bool check() {
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
            if(G[i][j]) return false;
    return true;
}

bool Step(int d) {
    if(d>N) {
        do {
            down();
        }while(clean());
        return check();
    }
    int G0[maxn][maxm];
    bool flag=true;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=7;j++)
            if(G[i][j]!=0) {
                flag=false;
                if(i<5) {
                    memcpy(G0,G,sizeof(G));
                    move_block(ans[d]=Point(i,j),op[d]=1);
                    if(!Step(d+1)) {
                        memcpy(G,G0,sizeof(G0));
                        ans[d]=Point(0,0);
                        op[d]=0;
                    } else return true;
                }
                if(i>1&&G[i-1][j]==0) {
                    memcpy(G0,G,sizeof(G));
                    move_block(ans[d]=Point(i,j),op[d]=-1);
                    if(!Step(d+1)) {
                        memcpy(G,G0,sizeof(G0));
                        ans[d]=Point(0,0);
                        op[d]=0;
                    } else return true;
                }
            }
    return flag;
}

int main() {
    scanf("%d",&N);
    for(int i=1;i<=5;i++)
        for(int j=1;;j++) {
            scanf("%d",&G[i][j]);
            if(!G[i][j]) break;
        }
    if(Step(1)) {
        for(int i=1;i<=N;i++)
            printf("%d %d %d\n",ans[i].x-1,ans[i].y-1,op[i]);
        return 0;
    }
    printf("-1");
    return 0;
}