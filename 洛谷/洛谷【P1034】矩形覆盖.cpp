#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 55
#define MAXK 5

struct Square {
    int x,y;
    bool operator < (const Square&q)const {
        if(y==q.y) return x<q.x;
        return y<q.y;
    }
};

Square a[MAXN];
int f[MAXN][MAXN][MAXK];

int main() {
    memset(f,127/3,sizeof(f));
    int n,k,l,r;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) {
        l=r=a[i].x;
        for(int j=i;j<=n;j++) {
            l=min(l,a[j].x),r=max(r,a[j].x);
            f[i][j][1]=(a[j].y-a[i].y)*(r-l);
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int kk=i;kk<j;kk++)
                f[i][j][2]=min(f[i][kk][1]+f[kk+1][j][1],f[i][j][2]);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int kk=i;kk<j;kk++) {
                f[i][j][3]=min(f[i][kk][1]+f[kk+1][j][2],f[i][j][3]);
                f[i][j][3]=min(f[i][kk][2]+f[kk+1][j][1],f[i][j][3]);
            }
    printf("%d",f[1][n][k]);
    return 0;
}