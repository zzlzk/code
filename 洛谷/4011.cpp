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

#define MAXN 11

const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};

int door[MAXN][MAXN][MAXN][MAXN];
int key[MAXN][MAXN];

struct State {
    int x,y,s;
    State(int x=0,int y=0,int s=0):
        x(x),y(y),s(s) {}
};

int n,m,p,k;
queue<State> q;
int dis[MAXN][MAXN][(1<<16)+10];
bool inq[MAXN][MAXN][(1<<16)+10];

#define door(_,a,b) door[_.x][_.y][a][b]
#define dis(_) dis[_.x][_.y][_.s]

bool can(int x,int y) {
    return x>0&&x<=n&&y>0&&y<=m;
}

#define inf 2147483647

void spfa() {
    for(int i=0;i<11;i++)
        for(int j=0;j<11;j++)
            for(int s=0;s<((1<<16)+10);s++)
                dis[i][j][s]=inf;
    q.push(State(1,1,0)),
    dis[1][1][0]=0,
    inq[1][1][0]=true;
    if(key[1][1]) {
        q.push(State(1,1,key[1][1])),
        dis[1][1][key[1][1]]=0,
        inq[1][1][key[1][1]]=true;
    }
    while(!q.empty()) {
        State c=q.front();
        q.pop();
        inq[c.x][c.y][c.s]=false;
        for(int i=0,x,y,s;i<4;i++) {
            x=c.x+dx[i],y=c.y+dy[i],s=c.s;
            if(!can(x,y)) continue;
            if(door(c,x,y)==-1) continue;
            if((door(c,x,y)&s)!=door(c,x,y)) continue;
            if(dis[x][y][s]>dis(c)+1) {
                dis[x][y][s]=dis(c)+1;
                if(!inq[x][y][s]) {
                    q.push(State(x,y,s));
                    inq[x][y][s]=true;
                }
            }
            if(!key[x][y]) continue;
            if(dis[x][y][s|key[x][y]]>dis(c)+1) {
                dis[x][y][s|key[x][y]]=dis(c)+1;
                if(!inq[x][y][s|key[x][y]]) {
                    q.push(State(x,y,s|key[x][y]));
                    inq[x][y][s|key[x][y]]=true;
                }
            }
        }
    }
    return;
}

int main() {
    input(n),input(m),input(p),input(k);
    for(int i=1,a,b,c,d,g;i<=k;i++) {
        input(a),input(b),input(c),input(d),input(g);
        if(g) {
            door[a][b][c][d]|=1<<g,
            door[c][d][a][b]|=1<<g;
        } else {
            door[a][b][c][d]=-1,
            door[c][d][a][b]=-1;
        }
    }
    input(k);
    for(int i=1,a,b,q;i<=k;i++) {
        input(a),input(b),input(q);
        key[a][b]|=1<<q;
    }
    spfa();
    int ans=inf;
    for(int i=0;i<(1<<(k+1));i++)
        ans=min(ans,dis[n][m][i]);
    printf("%d\n",ans==inf?-1:ans);
    return 0;
}
