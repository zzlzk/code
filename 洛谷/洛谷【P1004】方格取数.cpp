#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 20
int dp[maxn][maxn][maxn][maxn];
int G[maxn][maxn]={0};
int main() {
	int n,a,b,c;
	scanf("%d",&n);
	while(scanf("%d%d%d",&a,&b,&c))
		if(a==0&&b==0&&c==0) break;
		else G[a][b]=c;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++) for(int l=1;l<=n;l++) {
			int &f=dp[i][j][k][l];
			f=max(f,dp[i-1][j][k][l-1]);
			f=max(f,dp[i][j-1][k-1][l]);
			f=max(f,dp[i-1][j][k-1][l]);
			f=max(f,dp[i][j-1][k][l-1]);
			f+=G[i][j];
			if(k!=i||l!=j) f+=G[k][l];
		}
	printf("%d\n",dp[n][n][n][n]);
	return 0;
}
