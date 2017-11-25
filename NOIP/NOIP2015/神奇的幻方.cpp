#include<cstdio>
using namespace std;
#define maxn 45
struct NUM {
    int x,y;
    NUM(int x=0,int y=0):
        x(x),y(y) {}
}num[maxn*maxn];
int a[maxn][maxn]={0};
int main() {
    int n;
    scanf("%d",&n);
    a[1][1+n>>1]=1;
    num[1]=NUM(1,1+n>>1);
    for(int k=2;k<=n*n;k++) {
        int x,y;
        if(num[k-1].x==1&&num[k-1].y!=n) x=n,y=num[k-1].y+1;
        else if(num[k-1].x!=1&&num[k-1].y==n) y=1,x=num[k-1].x-1;
        else if(num[k-1].x==1&&num[k-1].y==n) x=num[k-1].x+1,y=num[k-1].y;
        else if(num[k-1].x!=1&&num[k-1].y!=n) {
            int i=num[k-1].x,j=num[k-1].y;
            if(a[i-1][j+1]==0) x=i-1,y=j+1;
            else x=i+1,y=j;
        }
        num[k]=NUM(x,y);
        a[x][y]=k;
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    return 0;
}