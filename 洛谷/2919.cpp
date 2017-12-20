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

#define MAXN 710
#define MAXM 710

struct Point {
    int x,y,h;
    Point(int x=0,int y=0,int h=0):
        x(x),y(y),h(h) {}
    bool operator < (const Point &q) const {
        return h>q.h;
    }
};

Point a[MAXN*MAXM];
int cnt;

void add(int x,int y,int h) {
    a[++cnt]=Point(x,y,h);
    return;
}

const int dx[]={0,0,1,-1,1,1,-1,-1};
const int dy[]={1,-1,0,0,1,-1,1,-1};

int n,m;
int height[MAXN][MAXM];
bool vis[MAXN][MAXM];

#define height(_) height[_.x][_.y]
#define vis(_) vis[_.x][_.y]
#define inmap(_) (_.x>=1&&_.x<=n&&_.y>=1&&_.y<=m)

void dfs(Point now) {
    vis(now)=true;
    Point v;
    for(int i=0;i<8;i++) {
        v.x=now.x+dx[i];
        v.y=now.y+dy[i];
        if(!inmap(v)) continue;
        if(!vis(v)&&height(v)<=height(now))
            dfs(v);
    }
    return;
}

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            input(height[i][j]);
            add(i,j,height[i][j]);
        }
    sort(a+1,a+cnt+1);
    int ans=0;
    for(int i=1;i<=cnt;i++)
        if(!vis(a[i])) {
            dfs(a[i]);
            ans++;
        }
    printf("%d",ans);
    return 0;
}
