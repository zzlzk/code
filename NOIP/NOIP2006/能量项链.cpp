#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 210
int dp[maxn][maxn];
int power[maxn];
int main() {
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&power[i]),power[i+n]=power[i];
	for(int i=2;i<=n;i++)
		for(int l=1;l+i-1<n*2;l++) {
			int r=l+i-1;
			for(int k=l;k<r;k++)
				dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]+power[l]*power[k+1]*power[r+1]);
		}
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i][i+n-1]);
	printf("%d",ans);
	return 0;
}
