#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 110
int dp1[maxn],dp2[maxn];
int a[maxn],b[maxn];
int main() {
	int n,ans;
	scanf("%d",&n);
	ans=n;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		b[n-i+1]=a[i];
	}
	for(int i=1;i<=n;i++) {
		dp1[i]=1,dp2[i]=1;
		for(int j=1;j<i;j++) {
			if(a[j]<a[i]&&dp1[j]+1>dp1[i])
				dp1[i]=dp1[j]+1;
			if(b[j]<b[i]&&dp2[j]+1>dp2[i])
				dp2[i]=dp2[j]+1;
		}
	}
	for(int i=1;i<=n;i++) {
		int k=dp1[i]+dp2[n-i+1]-1;
		if(n-k<ans) ans=n-k;
	}
	printf("%d",ans);
	return 0;
}
