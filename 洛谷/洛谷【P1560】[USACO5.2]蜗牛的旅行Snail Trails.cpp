#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 130

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

int n,B;
int ans=-1;
int G[MAXN][MAXN];

#define inmap(x,y) (x>=1&&x<=n&&y>=1&&y<=n)

void dfs(int x,int y,int d,int nowans) {
    if(nowans>ans) ans=nowans;
    int xx=x+dx[d],yy=y+dy[d];
    if(G[xx][yy]==1&&inmap(xx,yy)) {
        G[xx][yy]=-1;
        dfs(xx,yy,d,nowans+1);
        G[xx][yy]=1;
    } else if(G[xx][yy]==0)
        for(int i=0;i<4;i++) {
            xx=x+dx[i],yy=y+dy[i];
            if(!inmap(xx,yy)) continue;
            if(G[xx][yy]==1&&(i+d)%2!=0) {
                G[xx][yy]=-1;
                dfs(xx,yy,i,nowans+1);
                G[xx][yy]=1;
            }
        }
    return;
}

int main() {
    scanf("%d%d",&n,&B);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            G[i][j]=1;
    char c;
    for(int i=1,j;i<=B;i++) {
        cin>>c>>j;
        G[c-'A'+1][j]=0;
    }
    dfs(1,1,0,1);
    dfs(1,1,1,1);
    printf("%d",ans);
    return 0;
}
