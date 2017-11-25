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
    for(;c<'0' or c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0' and c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 310
#define MAXM 310

const int dx[]={0,0,0,1,-1};
const int dy[]={0,1,-1,0,0};


struct Point {
    int x,y;
    Point(int x=0,int y=0):
        x(x),y(y) {}
};

struct Star {
    Point pos;
    int Time;
};

int CanMove[MAXN][MAXM];
#define CanMove(_) CanMove[_.x][_.y]

queue<Star> q;
bool inq[MAXN][MAXM];

#define inq(_) inq[_.x][_.y]
#define inf 0x7fffffff

void bfs() {
    Star u,v;
    u.pos=Point(0,0);
    u.Time=0;
    q.push(u);
    inq(u.pos)=true;
    while(!q.empty()) {
        u=q.front();
        q.pop();
        for(int i=1;i<=4;i++) {
            v.pos=Point(u.pos.x+dx[i],u.pos.y+dy[i]);
            v.Time=u.Time+1;
            if(v.pos.x<0||v.pos.y<0) continue;
            if(CanMove(v.pos)==inf) {
                printf("%d",v.Time);
                exit(0);
            }
            if(!inq(v.pos)&&v.Time<CanMove(v.pos)) {
                q.push(v);
                inq(v.pos)=true;
            }
        }
    }
    return;
}

int main() {
    int m;
    input(m);
    for(int i=0;i<310;i++)
        for(int j=0;j<310;j++)
            CanMove[i][j]=inf;
    for(int i=1,x,y,t;i<=m;i++) {
        input(x),input(y),input(t);
        for(int j=0,xx,yy;j<=4;j++) {
            xx=x+dx[j],yy=y+dy[j];
            if(xx<0||yy<0) continue;
            CanMove[xx][yy]=min(t,CanMove[xx][yy]);
        }
    }
    bfs();
    printf("-1");
    return 0;
}