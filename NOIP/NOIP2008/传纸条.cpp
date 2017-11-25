#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 55
int dp[maxn][maxn][maxn][maxn];
int G[maxn][maxn];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&G[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=n;k>=1;k--)
                for(int l=m;l>=1;l--) {
                    int &f=dp[i][j][k][l];
                    f=max(f,dp[i-1][j][k][l-1]);
                    f=max(f,dp[i][j-1][k-1][l]);
                    f=max(f,dp[i-1][j][k-1][l]);
                    f=max(f,dp[i][j-1][k][l-1]);
                    f+=G[i][j];
                    if(k!=i||l!=j) f+=G[k][l];
                }
    printf("%d",dp[n][m][n][m]);
    return 0;
}