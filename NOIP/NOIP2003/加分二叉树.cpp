#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define maxn 35
ll a[maxn],dp[maxn][maxn];
int root[maxn][maxn];
template<typename T>
inline void input(T &x) {
	x=0;
	T f=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	x*=f;
}
void Print(int l,int r) {
	if(l>r) return;
	if(l==r) {
		printf("%d ",l);
		return;
	}
	printf("%d ",root[l][r]);
	Print(l,root[l][r]-1);
	Print(root[l][r]+1,r);
	return;
}
int main() {
	int n;
	input(n);
	for(int i=1;i<=n;i++) {
		input(a[i]);
		dp[i][i]=a[i];
	}
	for(int i=1;i<=n;i++) dp[i][i-1]=1;
	for(int i=n;i>=1;i--)
		for(int j=i+1;j<=n;j++)
			for(int k=i;k<=j;k++)
				if(dp[i][k-1]*dp[k+1][j]+a[k]>dp[i][j]) {
					dp[i][j]=dp[i][k-1]*dp[k+1][j]+a[k];
					root[i][j]=k;
				}
	printf("%lld\n",dp[1][n]);
	Print(1,n);
	return 0;
}
