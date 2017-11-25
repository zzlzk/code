#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 65
#define maxV 32010
int dp[maxV];
int enc[maxn][6];
int v[maxn],w[maxn];
int main() {
	int V,n;
	scanf("%d%d",&V,&n);
	for(int i=1,e;i<=n;i++) {
		scanf("%d%d%d",&v[i],&w[i],&e);
		w[i]*=v[i];
		if(e==0) continue;
		enc[e][++enc[e][0]]=i;
		enc[i][5]=2333;
	}
	for(int i=1;i<=n;i++) {
		if(enc[i][5]==2333) continue;
		for(int j=V;j>=v[i];j--) {
			dp[j]=max(dp[j],dp[j-v[i]]+w[i]);
			int v1=v[enc[i][1]],w1=w[enc[i][1]];
			int v2=v[enc[i][2]],w2=w[enc[i][2]];
			if(j>=v[i]+v1) dp[j]=max(dp[j],dp[j-v[i]-v1]+w[i]+w1);
			if(j>=v[i]+v2) dp[j]=max(dp[j],dp[j-v[i]-v2]+w[i]+w2);
			if(j>=v[i]+v1+v2)
				dp[j]=max(dp[j],dp[j-v[i]-v1-v2]+w[i]+w1+w2);
		}
	}
	printf("%d",dp[V]);
	return 0;
}
